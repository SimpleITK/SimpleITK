#!/usr/bin/env groovy

// Jackson is a JSON parser
@Grab(group='org.codehaus.jackson', module='jackson-mapper-asl', version='1.8.0')

// "Grab" log4j
@Grab('log4j:log4j:1.2.16')
import org.codehaus.jackson.map.*
import org.codehaus.jackson.map.ObjectMapper

import org.apache.log4j.*

if ( this.args.size() != 2 ) {
  println ( "usage: GenerateDocumentation <SimpleITKClass.json> <Path/To/ITK-build/With/Doxygen>" )
  System.exit ( 1 )
}
// Read the JSON definition
def JSONFile = this.args[0]
def mapper = new ObjectMapper()
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
def XMLFileOptions = ["classitk_1_1" + definition.name + definition.template_code_filename + ".xml",
"classitk_1_1" + definition.name + "ImageFilter.xml"]

XMLFileOptions.each {
  def test = args[1] + "/Utilities/Doxygen/xml/" + it
  def f = new File ( test )
  if ( f.exists() && f.canRead() ) {
    XMLFile = f
  }
}
if ( !XMLFile ) {
  println ( "Could not  not exist, or is not readable, tried: " )
  XMLFileOptions.each { print it.name + " " }
  System.exit ( 1 )
}

def formatDescription ( parent ) {
  StringBuilder result = new StringBuilder()
  def prefix = [ "listitem" : "\\li ", "itemizedlist" : "\n", "ref" : " "]
  def postfix = [ "para" : "\n", "title" : "\n" ]

  // Go depth first
  parent.each {
    switch ( it.getClass() ) {
    case groovy.util.Node:
      if ( it.name() == "simplesect" ) {
        switch ( it.@kind ) {
        case "see":
          // The "see" simplesect should have each element formated with a \see, and then returned
          it.each { child ->
            result.append ( "\\see" + formatDescription ( child ) + "\n" )
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
      // Don't write anything out, if there is no content
      if ( sub.length() > 0 ) {
        result.append ( prefix.get(it.name(), '') )
        result.append ( sub )
        result.append ( postfix.get(it.name(), '') )
      }
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

doc.compounddef.sectiondef.memberdef.each { it ->
  if ( it.@kind == "function" ) {
    Map[it.name.text()] = [ name : it.name.text(), briefdescription : it.briefdescription, detaileddescription : it.detaileddescription, definition : it ]
  }
}


// Now, go through the JSON members and fill in doc strings
definition.briefdescription = formatDescription ( Map.Class.briefdescription )
definition.detaileddescription = formatDescription ( Map.Class.detaileddescription )

definition.members.each { member ->
  // Lookup the name...
  // println ( "Processing definition for " + member + " of class " + member.getClass() )
  // There may be Get and Set methods...
  ["", "Set", "Get"].each { prefix ->
    // println ( "\tHandling prefix: " + prefix )
    if ( ( tmp = Map[prefix + member.name] ) ) {
      // println ( "\tFound info: " + tmp )
      member["briefdescription"+prefix]    = formatDescription ( tmp.briefdescription )
      member["detaileddescription"+prefix] = formatDescription ( tmp.detaileddescription )
    }
  }
}


// Print our new JSON
mapper.configure(SerializationConfig.Feature.INDENT_OUTPUT, true);
mapper.writeValue(new File(JSONFile), definition);



