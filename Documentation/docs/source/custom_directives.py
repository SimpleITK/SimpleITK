from docutils.parsers.rst import Directive, directives
from docutils.statemachine import StringList
from docutils import nodes
import re
import os
import sphinx_gallery


class GalleryItemDirective(Directive):
    required_arguments = 1
    optional_arguments = 0
    final_argument_whitespace = True
    option_spec = {'figure': directives.unchanged,
                   'intro': directives.unchanged}
    has_content = False
    add_index = False

    def run(self):
        env = self.state.document.settings.env
        args = self.arguments
        fname = args[-1]
        fname, abs_fname = env.relfn2path(fname)
        basename = os.path.basename(fname)
        dirname = os.path.dirname(fname)

        try:
            if 'intro' in self.options:
                intro = self.options['intro'][:195] + '...'
            else:
                intro = sphinx_gallery.gen_rst.extract_intro(abs_fname)

            thumbnail_rst = sphinx_gallery.backreferences._thumbnail_div(dirname, basename, intro)

            if 'figure' in self.options:
                rel_figname, figname = env.relfn2path(self.options['figure'])
                save_figname = os.path.join('_static/thumbs/', os.path.basename(figname))

                try:
                    os.makedirs('_static/thumbs')
                except FileExistsError:
                    pass

                sphinx_gallery.gen_rst.scale_image(figname, save_figname, 400, 280)
                thumbnail_rst = re.sub(r'..\sfigure::\s.*\.png',
                                       '.. figure:: /{}'.format(save_figname),
                                       thumbnail_rst)

            thumbnail = StringList(thumbnail_rst.split('\n'))
            thumb = nodes.paragraph()
            self.state.nested_parse(thumbnail, self.content_offset, thumb)

            return [thumb]
        except FileNotFoundError as e:
            print(e)
            raise e
            return []
