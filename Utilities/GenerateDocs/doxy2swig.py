#!/usr/bin/env python
"""Doxygen XML to SWIG docstring converter.

Converts Doxygen generated XML files into a file containing docstrings
that can be used by SWIG-1.3.x.  Note that you need to get SWIG
version > 1.3.23 or use Robin Dunn's docstring patch to be able to use
the resulting output.

Usage:

  doxy2swig.py input.xml output.i

input.xml is your doxygen generated XML file and output.i is where the
output will be written (the file will be clobbered).

"""

# This code is implemented using Mark Pilgrim's code as a guideline:
#   http://www.faqs.org/docs/diveintopython/kgp_divein.html
#
# Author: Prabhu Ramachandran
# License: BSD style


#  This version of the script originated from ITK/Wrapping/Generators/Doc/doxy2swig.py.
#  My mods:
#    self.multi is always 1 (0 was cutting lines improperly)
#    added self.java to enable output for JavaDocs
#
#  Dave Chen

from xml.dom import minidom
import re
import textwrap
import sys
import types
import os.path
import getopt
import regex

debug = 0

def my_open_read(source):
    if hasattr(source, "read"):
        return source
    else:
        return open(source)

def my_open_write(dest, mode='w'):
    if hasattr(dest, "write"):
        return dest
    else:
        return open(dest, mode)


class Doxy2SWIG:
    """Converts Doxygen generated XML files into a file containing
    docstrings that can be used by SWIG-1.3.x that have support for
    feature("docstring").  Once the data is parsed it is stored in
    self.pieces.

    """

    def __init__(self, src, javaFlag=0):
        """Initialize the instance given a source object (file or
        filename).

        """
        f = my_open_read(src)
        self.my_dir = os.path.dirname(f.name)
        self.xmldoc = minidom.parse(f).documentElement
        f.close()

        self.pieces = []
#        self.pieces.append('\n// File: %s\n'%os.path.basename(f.name))

        self.space_re = re.compile(r'\s+')
        self.lead_spc = re.compile(r'^(%feature\S+\s+\S+\s*?)"\s+(\S)')

        self.java = javaFlag

        # self.multi was 0, but it was cutting lines improperly -Dave Chen
        self.multi = 1

        self.ignores = ('inheritancegraph', 'param', 'listofallmembers',
                        'innerclass', 'name', 'declname', 'incdepgraph',
                        'invincdepgraph', 'programlisting', 'type',
                        'references', 'referencedby', 'location',
                        'collaborationgraph', 'reimplements',
                        'reimplementedby', 'derivedcompoundref',
                        'basecompoundref')
        #self.generics = []

        # flag to tell when we're inside a <simplesect> node with kind=="see".
        self.insideSee = False
        self.printSee = False

    def generate(self):
        """Parses the file set in the initialization.  The resulting
        data is stored in `self.pieces`.

        """
        self.parse(self.xmldoc)

    def parse(self, node):
        """Parse a given node.  This function in turn calls the
        `parse_<nodeType>` functions which handle the respective
        nodes.

        """
        pm = getattr(self, "parse_%s"%node.__class__.__name__)
        pm(node)

    def parse_Document(self, node):
        self.parse(node.documentElement)

    def parse_Text(self, node):
        txt = node.data
        txt = txt.replace('\\', r'\\\\')
        txt = txt.replace('"', r'\"')
        # ignore pure whitespace
        m = self.space_re.match(txt)
        if m and len(m.group()) == len(txt):
            pass
        else:
            #if we're in a "See" node and starting a new line, indent one space
            if self.insideSee and len(self.pieces) and self.pieces[-1][-1] == '\n':
                self.add_text(' ')
            self.add_text(textwrap.fill(txt))

    def parse_Element(self, node):
        """Parse an `ELEMENT_NODE`.  This calls specific
        `do_<tagName>` handers for different elements.  If no handler
        is available the `generic_parse` method is called.  All
        tagNames specified in `self.ignores` are simply ignored.

        """
        name = node.tagName
        ignores = self.ignores
        if name in ignores:
            return
        attr = "do_%s" % name
        if hasattr(self, attr):
            handlerMethod = getattr(self, attr)
            handlerMethod(node)
        else:
            self.generic_parse(node)
            #if name not in self.generics: self.generics.append(name)

    def add_text(self, value):
        """Adds text corresponding to `value` into `self.pieces`."""
        if type(value) in (list, tuple):
            self.pieces.extend(value)
        else:
            self.pieces.append(value)

    def get_specific_nodes(self, node, names):
        """Given a node and a sequence of strings in `names`, return a
        dictionary containing the names as keys and child
        `ELEMENT_NODEs`, that have a `tagName` equal to the name.

        """
        nodes = [(x.tagName, x) for x in node.childNodes \
                 if x.nodeType == x.ELEMENT_NODE and \
                 x.tagName in names]
        return dict(nodes)

    def generic_parse(self, node, pad=0):
        """A Generic parser for arbitrary tags in a node.

        Parameters:

         - node:  A node in the DOM.
         - pad: `int` (default: 0)

           If 0 the node data is not padded with newlines.  If 1 it
           appends a newline after parsing the childNodes.  If 2 it
           pads before and after the nodes are processed.  Defaults to
           0.

        """
        if debug:
            print "Generic parse: ", node, node.__class__.__name__, node.tagName, self.pieces[-5:]

        npiece = 0
        if pad:
            npiece = len(self.pieces)
            if pad == 2:
                self.add_text('\n')

        if debug:
            print len(node.childNodes), "children"
            for n in node.childNodes:
                print "child: ", n, n.__class__.__name__
                if n.__class__.__name__ == "Element":
                    print n.tagName

        firstSee = True
        for n in node.childNodes:
            if n.__class__.__name__ == "Element":
                if n.tagName == "simplesect":
                    kind = n.attributes['kind'].value
                    if kind == "see":
                        if debug:
                            print "simplesect attributes:", n.attributes
                        if firstSee:
                            n.setAttribute("PrintSee", "1")
                        firstSee = False
                    else:
                        firstSee = True
                else:
                    firstSee = True
            self.parse(n)
        if pad:
            if len(self.pieces) > npiece:
                self.add_text('\n')
        if debug:
            print ""

    def space_parse(self, node):
        """ Only output a space if the last character outputed was not a new line.
            I.e., don't allow a line to lead with a space.
        """
        if len(self.pieces) and self.pieces[-1][-1] != '\n':
          self.add_text(' ')
        self.generic_parse(node)

    # The handlers for all these node types get mapped to a space
    do_ref = space_parse
    do_ulink = space_parse
    do_emphasis = space_parse
    do_bold = space_parse
    do_computeroutput = space_parse
    do_formula = space_parse

    def do_compoundname(self, node):
        self.add_text('\n\n')
        data = node.firstChild.data
        if self.java:
            self.add_text('%%typemap(javaimports) %s "/**\n'%data)
        else:
            self.add_text('%%feature("docstring") %s "\n'%data)

    def do_compounddef(self, node):
        kind = node.attributes['kind'].value
        if kind in ('class', 'struct'):
            prot = node.attributes['prot'].value
            if prot != 'public':
                return
            names = ('compoundname', 'briefdescription',
                     'detaileddescription', 'includes')
            first = self.get_specific_nodes(node, names)
            for n in names:
                if n in first:
                    self.parse(first[n])
            if self.java:
                self.add_text(['*/"','\n'])
            else:
                self.add_text(['";','\n'])
            for n in node.childNodes:
                if n not in list(first.values()):
                    self.parse(n)
        elif kind in ('file', 'namespace'):
            nodes = node.getElementsByTagName('sectiondef')
            for n in nodes:
                self.parse(n)

    def do_includes(self, node):
        self.add_text('C++ includes: ')
        self.generic_parse(node, pad=1)

    def do_parameterlist(self, node):
        self.add_text(['\n', '\n', 'Parameters:', '\n'])
        self.generic_parse(node, pad=1)

    def do_para(self, node):
        self.add_text('\n')
        self.generic_parse(node, pad=1)

    def do_parametername(self, node):
        self.add_text('\n')
        self.add_text("%s: "%node.firstChild.data)

    def do_parameterdefinition(self, node):
        self.generic_parse(node, pad=1)

    def do_detaileddescription(self, node):
        self.generic_parse(node, pad=1)

    def do_briefdescription(self, node):
        self.generic_parse(node, pad=1)

    def do_memberdef(self, node):
        prot = node.attributes['prot'].value
        id = node.attributes['id'].value
        kind = node.attributes['kind'].value
        tmp = node.parentNode.parentNode.parentNode
        compdef = tmp.getElementsByTagName('compounddef')[0]
        cdef_kind = compdef.attributes['kind'].value

        if prot == 'public':
            first = self.get_specific_nodes(node, ('definition', 'name'))
            name = first['name'].firstChild.data
            if name[:8] == 'operator': # Don't handle operators yet.
                return

            defn = first['definition'].firstChild.data
            self.add_text('\n')
            if self.java:
                self.add_text('%javamethodmodifiers ')
            else:
                self.add_text('%feature("docstring") ')

            anc = node.parentNode.parentNode
            if cdef_kind in ('file', 'namespace'):
                ns_node = anc.getElementsByTagName('innernamespace')
                if not ns_node and cdef_kind == 'namespace':
                    ns_node = anc.getElementsByTagName('compoundname')
                if ns_node:
                    ns = ns_node[0].firstChild.data
                    if self.java:
                        self.add_text(' %s::%s "/**\n%s'%(ns, name, defn))
                    else:
                        self.add_text(' %s::%s "\n'%(ns, name))
                else:
                    if self.java:
                        self.add_text(' %s "/**\n%s'%(name, defn))
                    else:
                        self.add_text(' %s "\n'%(name))
            elif cdef_kind in ('class', 'struct'):
                # Get the full function name.
                anc_node = anc.getElementsByTagName('compoundname')
                cname = anc_node[0].firstChild.data
                if self.java:
                    self.add_text(' %s::%s "/**\n%s'%(cname, name, defn))
                else:
                    self.add_text(' %s::%s "\n'%(cname, name))

            for n in node.childNodes:
                if n not in list(first.values()):
                    self.parse(n)
            if self.java:
              self.add_text(['*/\npublic ";', '\n'])
            else:
              self.add_text(['";', '\n'])

    def do_definition(self, node):
        data = node.firstChild.data
        self.add_text('%s "\n%s'%(data, data))

    def do_sectiondef(self, node):
        kind = node.attributes['kind'].value
        if kind in ('public-func', 'func'):
            self.generic_parse(node)

    def do_simplesect(self, node):
        if debug:
            print "Simplesect"
        kind = node.attributes['kind'].value
        if kind in ('date', 'rcs', 'version'):
            pass
        elif kind == 'warning':
            self.add_text(['\n', 'WARNING:'])
            self.generic_parse(node)
        elif kind == 'see':
            if node.getAttribute("PrintSee"):
                if debug:
                    print "Printing See"
                self.add_text('\n')
                self.add_text('See:')
            self.insideSee = True
            self.generic_parse(node)
            self.insideSee = False
        else:
            self.generic_parse(node)

    def do_argsstring(self, node):
        if self.java:
            self.generic_parse(node, pad=1)

    def do_member(self, node):
        kind = node.attributes['kind'].value
        refid = node.attributes['refid'].value
        if kind == 'function' and refid[:9] == 'namespace':
            self.generic_parse(node)

    def do_doxygenindex(self, node):
        self.multi = 1
        comps = node.getElementsByTagName('compound')
        for c in comps:
            refid = c.attributes['refid'].value
            fname = refid + '.xml'
            if not os.path.exists(fname):
                fname = os.path.join(self.my_dir,  fname)
#            print "parsing file: %s"%fname
            p = Doxy2SWIG(fname)
            p.generate()
            self.pieces.extend(self.clean_pieces(p.pieces))

    def write(self, fname, mode='w'):
        o = my_open_write(fname, mode)
        if self.multi:
            o.write("".join(self.pieces))
        else:
            o.write("".join(self.clean_pieces(self.pieces)))
        o.close()

    def clean_pieces(self, pieces):
        """Cleans the list of strings given as `pieces`.  It replaces
        multiple newlines by a maximum of 2 and returns a new list.
        It also wraps the paragraphs nicely.

        """
        ret = []
        count = 0
        for i in pieces:
            if i == '\n':
                count = count + 1
            else:
                if i == '";':
                    if count:
                        ret.append('\n')
                elif count > 2:
                    ret.append('\n\n')
                elif count:
                    ret.append('\n'*count)
                count = 0
                ret.append(i)

        _data = "".join(ret)
        ret = []
        for i in _data.split('\n\n'):
            if i == 'Parameters:':
                ret.extend(['Parameters:\n-----------', '\n\n'])
            elif i.find('// File:') > -1: # leave comments alone.
                ret.extend([i, '\n'])
            else:
                _tmp = textwrap.fill(i.strip())
                _tmp = self.lead_spc.sub(r'\1"\2', _tmp)
                ret.extend([_tmp, '\n\n'])
        return ret


class Doxy2R(Doxy2SWIG):
    def __init__(self, src, javaFlag=0):
        Doxy2SWIG.__init__(self, src, javaFlag)
        """ Turns on the title, brief description and detailed description markup.
        Turn them off when inside member documentatation.

        """
        self.FilterTitle = True
        self.sitkClassName=''
        self.EmptyText = False
        # compiled regular expressions
        # common formula types in xml version of documentation
        self.dollarFormula = re.compile("^\\$(.+)\\$$")
        self.arrayFormula = re.compile("^\\\\\\[(.+)\\\\\\]$")
        # more complex formula layout, that breaks R documentation
        # checks.
        self.mathstuff1 = re.compile(r"\\begin\{array\}\{[^}]+\}")
        self.mathstuff2 = re.compile(r"\\begin\{array\}")
        self.mathstuff3 = re.compile(r"\\end\{array\}")
        # a complex recursive regular expression, to deal with formula
        # inside mbox and text structures
        self.mathstuff4 = regex.compile(r"\\mbox({((?>[^}{]*(?1)?)*)})", flags=regex.V1)
        self.mathstuff5 = regex.compile(r"\\text({((?>[^}{]*(?1)?)*)})", flags=regex.V1)
        # the special doxygen tags - note - not greedy
        self.mathstuff6 = re.compile(r"\\f\$(.+?)\\f\$")
        # alignment tags
        self.mathstuff7 = re.compile(r" & ")
        # Rd related issues - %, \" etc
        self.Rdpercent = re.compile("%")
        self.escapedquote=re.compile(r'\\"')

    def rdescape(self, value):
        """escape percent signs in Rd files"""
        v1=self.Rdpercent.sub(r"\%", value)
        v1=self.escapedquote.sub(r'"', v1)
        return(v1)

    def add_text(self, value):
        """Adds text corresponding to `value` into `self.pieces`."""
        if type(value) in (list, tuple):
            value=[self.rdescape(x) for x in value]
            self.pieces.extend(value)
        else:
            value=self.rdescape(value)
            self.pieces.append(value)

    def filterLatexMath(self, txt):
        """
        Removes the more complex formatting from latex formula.
        R documentation format doesn't deal with structures like
        equation arrays or the various boxes.
        """
        m1 = self.mathstuff1.sub("", txt)
        m1 = self.mathstuff2.sub("", m1)
        m1 = self.mathstuff3.sub("", m1)
        if self.mathstuff4.search(m1) is not None:
           (m1, cc) = self.mathstuff4.subn(r"\2", m1)
           (m1, cc) = self.mathstuff6.subn(r"\1", m1)
        if self.mathstuff5.search(m1) is not None:
           (m1, cc) = self.mathstuff5.subn(r"\2", m1)
           (m1, cc) = self.mathstuff6.subn(r"\1", m1)
        (m1, cc) = self.mathstuff7.subn(" ", m1)
        return(m1)

    def parse_Text(self, node):
        txt = node.data
        txt = txt.replace('\\', r'\\\\')
        txt = txt.replace('"', r'\"')
        # ignore pure whitespace
        m = self.space_re.match(txt)
        if m and len(m.group()) == len(txt):
            # Flag the text being empty
            self.EmptyText = True
            pass
        else:
            self.add_text(textwrap.fill(txt))

    def do_formula(self, node):
        # need to apply different tags if it is $$ or \[
        if len(self.pieces):
            txt = node.firstChild.data
            # does txt contain $
            f1 = self.dollarFormula.match(txt)
            f2 = self.arrayFormula.match(txt)
            if f1 is not None:
                self.add_text(' \\eqn{')
                self.add_text(self.filterLatexMath(f1.group(1)))
            elif f2 is not None:
                self.add_text(' \\deqn{')
                self.add_text(self.filterLatexMath(f2.group(1)))
            else:
                print("Unmatched formula")
                print(txt)

            self.add_text("}")

    def do_compoundname(self, node):
        self.add_text('\n\n')
        data = node.firstChild.data
        self.add_text('\\name{%s}\n'%data)
        self.add_text('\\Rdversion{1.1}\n\\docType{class}\n')
        self.sitkClassName=data

    def do_compounddef(self, node):
        kind = node.attributes['kind'].value
        if kind in ('class', 'struct'):
            prot = node.attributes['prot'].value
            if prot != 'public':
                return
            names = ('compoundname', 'briefdescription',
                     'detaileddescription', 'includes')
            first = self.get_specific_nodes(node, names)
            for n in names:
                if n in first:
                    self.parse(first[n])
            for n in node.childNodes:
                if n not in list(first.values()):
                    self.parse(n)
        elif kind in ('file', 'namespace'):
            nodes = node.getElementsByTagName('sectiondef')
            for n in nodes:
                self.parse(n)

    def do_includes(self, node):
        self.add_text('%C++ includes: ')
        self.generic_parse(node, pad=1)

    def do_detaileddescription(self, node):
        if self.FilterTitle:
            self.add_text('\\details{')
        self.generic_parse(node, pad=1)
        if self.FilterTitle:
            # check that we actually got a detailed description.
            # Not having a title is illegal in R
            # use the class name otherwise
            if self.EmptyText:
                self.add_text(self.sitkClassName)
            self.add_text('}\n')
    def do_briefdescription(self, node):
        # there are brief descriptions all over the place and
        # we don't want them all to be titles
        if self.FilterTitle:
            self.add_text('\\description{')
        self.generic_parse(node, pad=0)
        if self.FilterTitle:
            # if the title is empty, then we'll use the name
            if self.EmptyText:
                self.add_text(self.sitkClassName)
            self.add_text('}\n')
        self.EmptyText = False

    def do_memberdef(self, node):
        prot = node.attributes['prot'].value
        id = node.attributes['id'].value
        kind = node.attributes['kind'].value
        tmp = node.parentNode.parentNode.parentNode
        compdef = tmp.getElementsByTagName('compounddef')[0]
        cdef_kind = compdef.attributes['kind'].value

        self.FilterTitle = False;

        if prot == 'public':
            first = self.get_specific_nodes(node, ('definition', 'name'))
            name = first['name'].firstChild.data
            if name[:8] == 'operator': # Don't handle operators yet.
                return

            defn = first['definition'].firstChild.data
            self.add_text('\n')
            self.add_text('\\item{')
            anc = node.parentNode.parentNode
            # don't need to worry about documenting these in sitk
            if cdef_kind in ('file', 'namespace'):
                ns_node = anc.getElementsByTagName('innernamespace')
                if not ns_node and cdef_kind == 'namespace':
                    ns_node = anc.getElementsByTagName('compoundname')
                if ns_node:
                    ns = ns_node[0].firstChild.data
                    self.add_text('%s %s'%(name, defn))
                    if self.java:
                        self.add_text(' %s::%s "/**\n%s'%(ns, name, defn))
                    else:
                        self.add_text(' %s::%s "\n'%(ns, name))
                else:
                    self.add_text('YY %s TT %s'%(name, defn))
                    if self.java:
                        self.add_text(' %s "/**\n%s'%(name, defn))
                    else:
                        self.add_text(' %s "\n'%(name))
            ## everything will be a class
            elif cdef_kind in ('class', 'struct'):
                # Get the full function name.
                anc_node = anc.getElementsByTagName('compoundname')
                cname = anc_node[0].firstChild.data
                argstring = node.getElementsByTagName('argsstring')[0]
                arguments = argstring.firstChild.data
                returnType = node.getElementsByTagName('type')[0]
                if returnType.firstChild == None:
                    returnType = ''
                else:
                    ## search through the return type - 2 levels should be enough
                    ## usually there's a link around it.
                    if returnType.firstChild.firstChild != None:
                        returnType = returnType.firstChild.firstChild.nodeValue
                    else:
                        returnType = returnType.firstChild.nodeValue

                self.add_text('%s %s%s:}{'%(returnType, name, arguments))

            for n in node.childNodes:
                if n not in list(first.values()):
                    self.parse(n)
            self.add_text('}\n')
            self.FilterTitle=True;

    def do_sectiondef(self, node):
        kind = node.attributes['kind'].value
        if kind in ('public-func', 'func'):
            self.add_text('\\section{Methods}{\n\describe{')
            self.generic_parse(node)
            self.add_text('}\n}\n')

    def do_doxygenindex(self, node):
        self.multi = 1
        comps = node.getElementsByTagName('compound')
        for c in comps:
            refid = c.attributes['refid'].value
            fname = refid + '.xml'
            if not os.path.exists(fname):
                fname = os.path.join(self.my_dir,  fname)
#            print "parsing file: %s"%fname
            p = Doxy2R(fname)
            p.generate()
            self.pieces.extend(self.clean_pieces(p.pieces))

## For the procedural interface
## This will produce multiple Rd files, and is therefore
## quite different to the others
## Text is now stored in piecesdict
## add_text uses a variable to track the name

class Doxy2RProc(Doxy2SWIG):
    def __init__(self, src, javaFlag=0):
        Doxy2SWIG.__init__(self, src, javaFlag)
        """ Turns on the title, brief description and detailed description markup.
        Turn them off when inside member documentatation.

        """
        self.FilterTitle = True
        self.EmptyText = False
        self.piecesdict = dict()
        self.currentFunc=''
        self.NotesCPP=dict()

    def parse_Text(self, node):
        txt = node.data
        txt = txt.replace('\\', r'\\\\')
        txt = txt.replace('"', r'\"')
        # ignore pure whitespace
        m = self.space_re.match(txt)
        if m and len(m.group()) == len(txt):
            # Flag the text being empty
            self.EmptyText = True
            pass
        else:
            self.add_text(textwrap.fill(txt))

    def add_text(self, value):
        """Adds text corresponding to `value` into `self.pieces`."""
        if not self.currentname in self.piecesdict:
            self.piecesdict[self.currentname]=[]
        if type(value) in (list, tuple):
            self.piecesdict[self.currentname].extend(value)
        else:
            self.piecesdict[self.currentname].append(value)


    def do_includes(self, node):
        self.add_text('%C++ includes: ')
        self.generic_parse(node, pad=1)

    def do_detaileddescription(self, node):
        if self.FilterTitle:
            self.add_text('\\details{')
        self.generic_parse(node, pad=1)
        if self.FilterTitle:
            # check that we actually got a detailed description.
            # Not having a title is illegal in R
            # use the class name otherwise
            if self.EmptyText:
                self.add_text(self.sitkClassName)
            self.add_text('}\n')
    def do_briefdescription(self, node):
        # there are brief descriptions all over the place and
        # we don't want them all to be titles
        if self.FilterTitle:
            self.add_text('\\description{')
        self.generic_parse(node, pad=0)
        if self.FilterTitle:
            # if the title is empty, then we'll use the name
            if self.EmptyText:
                self.add_text(self.sitkClassName)
            self.add_text('}\n')
        self.EmptyText = False

    def do_memberdef(self, node):
        prot = node.attributes['prot'].value
        id = node.attributes['id'].value
        kind = node.attributes['kind'].value
        tmp = node.parentNode.parentNode.parentNode
        compdef = tmp.getElementsByTagName('compounddef')[0]
        cdef_kind = compdef.attributes['kind'].value
        self.FilterTitle = False;

        if prot == 'public':
            first = self.get_specific_nodes(node, ('definition', 'name'))
            name = first['name'].firstChild.data
            if name[:8] == 'operator': # Don't handle operators yet.
                return
            # names are overloaded, of course, and need
            # to be collected into the same R file
            defn = first['definition'].firstChild.data
            anc = node.parentNode.parentNode
            # need to worry about documenting these for the procedural interface
            # We want to document overloaded names in the same file,
            # which means we'll need to store a map of individual
            # file contents
            if cdef_kind in ('namespace'):
                # do we already have something by this name
                self.currentname=name
                others = self.get_specific_nodes(node, ('argsstring', 'briefdescription',
                                                        'detaileddescription'))
                argstring = others['argsstring'].firstChild.data
                if not name in self.piecesdict:
                    # first time we've hit this name, so add the name, alias and title
                    self.add_text('\\title{%s}\n' %(name))
                    self.add_text('\\name{%s}\n' %(name))
                    self.add_text('\\alias{%s}\n' %(name))
                    self.add_text('\\description{\n')
                    if others['briefdescription'] is None or \
                       others['briefdescription'].firstChild.data.isspace() or \
                       others['briefdescription'].firstChild.data == '':
                       ## not creating a link because the guess isn't always correct. There
                       ## are things like the TransformInitializerFilter family that don't
                       ## match this pattern.
                       self.add_text('See class definition - most likely %sImageFilter' %(name))
                    else:
                       self.generic_parse(others['briefdescription'])
                    self.add_text('\n}\n\n')
                    self.add_text('\\details{\n')
                    if others['detaileddescription'] is None or \
                       others['detaileddescription'].firstChild.data.isspace() or \
                       others['detaileddescription'].firstChild.data == '':
                       ## not creating a link because the guess isn't always correct. There
                       ## are things like the TransformInitializerFilter family that don't
                       ## match this pattern.
                      self.add_text('See class definition - most likely %sImageFilter' %(name))
                    else:
                       self.generic_parse(others['detaileddescription'])
                    self.add_text('\n}\n\n')

                # now the potentially repeated bits (overloading)
                # Rd doesn't allow multiple usage statements, so
                # collect them. Changed to using a note section, as
                # usage needs to be R code, not c++
                notecpp=defn + argstring
                if not name in self.NotesCPP:
                    self.NotesCPP[self.currentname]=""

                self.NotesCPP[self.currentname] = self.NotesCPP[self.currentname] + '\n\n' + notecpp

    def do_sectiondef(self, node):
        kind = node.attributes['kind'].value
        if kind in ('public-func', 'func', 'user-defined'):
            self.generic_parse(node)

    def write(self, fname, mode='w'):
        ## fname is the destination folder
        if os.path.isdir(fname):
            for FuncName in self.piecesdict:
                if FuncName == '' or \
                   FuncName.isspace() or \
                   FuncName == '\n':
                    continue
                outname=os.path.join(fname, FuncName + ".Rd")
                ## add the note to the end
                if FuncName in self.NotesCPP:
                    self.currentname=FuncName
                    notecpp = '\\note{\n%s\n}\n' % self.NotesCPP[FuncName]
                    self.add_text(notecpp)
                self.pieces = self.piecesdict[FuncName]
                Doxy2SWIG.write(self,outname)
        else:
            assert False, "Destination path doesn't exist"

def main(input, output):
    p = Doxy2SWIG(input)
    p.generate()
    p.write(output)

def usage():
    print ""
    print ("doxy2swig.py [options] input.xml output.i")
    print ""
    print ("  -h, --help                  This message")
    print ("  -d, --debug                 Debug")
    print ""


if __name__ == '__main__':

    try:
        opts, args = getopt.getopt(sys.argv[1:], "dh", [ "debug", "help" ] )
    except getopt.GetoptError, err:
        print (str(err))
        usage()
        sys.exit(2)

    for o, a in opts:
        if o in ("-d", "--debug"):
            debug = debug + 1
        elif o in ("-h", "--help"):
            usage()
            sys.exit()
        else:
            assert False, "unhandled options"


    if len(args) != 2:
        usage()
        sys.exit(1)
    main(args[0], args[1])
