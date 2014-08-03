#!/usr/bin/env groovy
/*=========================================================================
*
*  Copyright Insight Software Consortium
*
*  Licensed under the Apache License, Version 2.0 (the "License");
*  you may not use this file except in compliance with the License.
*  You may obtain a copy of the License at
*
*         http://www.apache.org/licenses/LICENSE-2.0.txt
*
*  Unless required by applicable law or agreed to in writing, software
*  distributed under the License is distributed on an "AS IS" BASIS,
*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*  See the License for the specific language governing permissions and
*  limitations under the License.
*
*=========================================================================*/

// Jackson is a JSON parser
@Grab(group='org.codehaus.jackson', module='jackson-mapper-asl', version='1.8.0')

// "Grab" log4j
@Grab('log4j:log4j:1.2.16')
import org.codehaus.jackson.map.*
import org.codehaus.jackson.*

import org.apache.log4j.*

if ( this.args.size() != 2 ) {
  println ( "usage: GenerateDocumentation <SimpleITKClass.json> <Path/To/ITK-build/With/Doxygen>" )
  System.exit ( 1 )
}
// Read the JSON definition
def JSONFile = this.args[0]
def mapper = new ObjectMapper()
// Allow comments (C and C++ style).  NB: these get blown away when we rewrite the file, caveat emptor
mapper.configure(JsonParser.Feature.ALLOW_COMMENTS, true);
def definition
try {
  // Try using jackson
  definition = mapper.readValue( new File ( JSONFile ), Map.class)
} catch ( IOException e ) {
  println ( "Failed to parse " + JSONFile + " usually means there was a parse error: " + e )
  System.exit ( 1 )
}

// Find the matching XML file
def XMLFile = null

// Find some options...
def XMLFileOptions = ["classitk_1_1" + definition.itk_name + ".xml",
                      "classitk_1_1" + definition.name + definition.template_code_filename + ".xml",
                      "classitk_1_1" + definition.name + ".xml"]

XMLFileOptions.each {
  def test = args[1] + "/"+ it
  def f = new File ( test )
  if ( f.exists() && f.canRead() ) {
    XMLFile = f
  }
}
if ( !XMLFile ) {
  println ( "Tried to read a file for " + definition.name + " tried: " + XMLFileOptions )
  System.exit ( 1 )
}


def formatDescription ( parent ) {
  StringBuilder result = new StringBuilder()
  def prefix = [ "listitem" : "\\li ",
                 "itemizedlist" : "\n",
                 "computeroutput" : " ",
                 "programlisting" : "\\code\n"]
  def postfix = [ "para" : "\n\n",
                  "title" : "\n",
                  "computeroutput" : " ",
                  "ref" : " ",
                  "ulink" : " ",
                  "codeline" : "\n",
                  "programlisting" : "\\endcode\n",
                  "sp" : " "]

  // Go depth first
  parent.each {
    switch ( it.getClass() ) {
    case groovy.util.Node:
      if ( it.name() == "simplesect" ) {
        switch ( it.@kind ) {
        case "see":
          // The "see" simplesect should have each element formated with a \see, and then returned
          it.each { child ->
            result.append ( "\\see " + formatDescription ( child ) + "\n" )
          }
          return result.toString()
          break
        default:
          result.append ( "\\" + it.@kind + " " )
        }
      }
      sub = formatDescription ( it.value() )
      // Need to properly format formula tags...
      if ( it.name() == "formula" ) {
        sub = sub.replaceFirst ( "\\\\\\[", " \\\\f[" ).replaceAll ( "\\]", "\\f] " )
        sub = sub.replaceAll ( "\\\$", "\\\\\\f\\\$" ) + " "
      }

      // add a leading spacing for "ulink" or "ref" nodes
      if ( ((it.name() == "ulink") || (it.name() == "ref")) && result.length()) {
        // check that there isn't a space already
        if (result.charAt(result.length()-1) != ' ') {
          result.append( " " )
        }
      }
      result.append ( prefix.get(it.name(), '') )
      result.append ( sub )
      result.append ( postfix.get(it.name(), '') )

      break
    case String:
      result.append ( it )
      break
    default:
      result.append ( it )
      break
    }
  }
  return result.toString()
}

// Fill in a map of Doxygen-generated info
def Map = [:]

def doc = new XmlParser().parse ( XMLFile )
Map['Class'] = [ name : doc.compounddef.compoundname.text(), briefdescription : doc.compounddef.briefdescription, detaileddescription : doc.compounddef.detaileddescription ]

println ( "Class: " + doc.compounddef.compoundname.text() )
def ClassName = doc.compounddef.compoundname.text().replaceAll ( "itk::", "itk::simple::" )
def ShortClassName = ClassName.tokenize ( "::" )[-1]

doc.compounddef.sectiondef.memberdef.each { it ->
  if ( it.@kind == "function" ) {
    Map[it.name.text()] = [ name : it.name.text(), briefdescription : it.briefdescription, detaileddescription : it.detaileddescription, definition : it ]
  }
}


// Now, go through the JSON members and fill in doc strings
definition.briefdescription = formatDescription ( Map.Class.briefdescription ).trim()
definition.detaileddescription = formatDescription ( Map.Class.detaileddescription ).trim()


definition.members.each { member ->
  // Lookup the name...
  // println ( "Processing definition for " + member + " of class " + member.getClass() )
  // There may be Get and Set methods...
  ["", "Set", "Get"].each { prefix ->
    // println ( "\tHandling prefix: " + prefix )
    if ( ( tmp = Map[prefix + member.name] ) ) {
      // println ( "\tFound info: " + tmp )
      member["briefdescription"+prefix]    = formatDescription ( tmp.briefdescription ).trim()
      member["detaileddescription"+prefix] = formatDescription ( tmp.detaileddescription ).trim()

    }
  }
}

definition.measurements.each { measurement ->
  // Lookup the name...
    //println ( "Processing definition for measurement " + measurement + " of class " + measurement.getClass() )
  // Only Get methods
  ["", "Get"].each { prefix ->
      //println ( "\tHandling prefix: " + prefix +"->"+prefix + measurement.name )
    if ( ( tmp = Map[prefix + measurement.name] ) ) {
      //println ( "\tFound info: " + tmp )
      measurement["briefdescription"+prefix]    = formatDescription ( tmp.briefdescription ).trim()
      measurement["detaileddescription"+prefix] = formatDescription ( tmp.detaileddescription ).trim()

    }
  }
}


// Print our new JSON
mapper.configure(SerializationConfig.Feature.INDENT_OUTPUT, true);
mapper.writeValue(new File(JSONFile), definition);



