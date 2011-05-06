#!/usr/bin/env groovy

// "Grab" the json-lib module from Sourceforge
@Grab(group='net.sf.json-lib', module='json-lib', version='2.4', classifier='jdk15')
import net.sf.json.groovy.*
GJson.enhanceClasses()

if ( this.args.size() != 2 ) {
  println ( "usage: GenerateDocumentation <SimpleITKClass.json> <Path/To/ITK-build/With/Doxygen>" )
  System.exit ( 1 )
}

// Read the JSON definition
def JSONFile = this.args[0]
def definition
try {
  definition = new JsonSlurper().parse ( new File ( JSONFile ) )
} catch ( all ) {
  println ( "Failed to parse " + JSONFile + " usually means there was a parse error" )
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
  def prefix = [ "listitem" : "\\li ", "itemizedlist" : "\n"]
  def postfix = [ "para" : "\n", "title" : "\n" ]

  parent.each {
    // Go depth first
    // println ( "Found: " + it.getClass() )
    switch ( it.getClass() ) {
      case groovy.util.Node:
        result.append ( prefix.get(it.name(), '') )
      // println ( "\trecurse: " + it.name() )
      if ( it.name() == "simplesect" ) { result.append ( "\\" + it.@kind + " " ) }
      if ( it.name() == "ref" ) { result.append ( " " ) }
      sub = formatDescription ( it.value() )
      if ( it.name() == "formula" ) {
        if ( sub.startsWith ( "\\\\\\[" ) ) {
          sub = sub.replaceFirst ( "\\\\\\[", " \\\\f[" ).replaceAll ( "\\]", "\\f] " )
        } else {
          sub = " \\f" + sub + "\\f "
        }
      }
      result.append ( sub )
      result.append ( postfix.get(it.name(), '') )
      break
      default:
        result.append ( it )
        // println ( "\treturn: " + it )
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
// println ( "Briefdescription: " + formatDescription ( doc.compounddef.briefdescription ) )
// println ( "Detailed: " + formatDescription ( doc.compounddef.detaileddescription ) )

doc.compounddef.sectiondef.memberdef.each { it ->
  if ( it.@kind == "function" ) {
    Map[it.name.text()] = [ name : it.name.text(), briefdescription : it.briefdescription, detaileddescription : it.detaileddescription, definition : it ]
    // println ( it.name.text() + ":\n" + formatDescription ( it.briefdescription ) + "\n" + formatDescription ( it.detaileddescription ) )
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
// println ( definition.toString ( 2 ) )
def fw = new FileWriter ( JSONFile )
fw.write ( definition.toString ( 2 ) )
fw.close()



