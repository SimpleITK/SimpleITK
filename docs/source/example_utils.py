# gaussian_utils.py
# This utility file hides most of the Example-specific code. The main() routine
# now returns both the input and output SITK images so they can be displayed
# individually.
import SimpleITK
import matplotlib.pyplot as plt
import importlib

# The Matplotlib plot_directive dpi default for png

from pathlib import Path
import os


DPI = 80


class set_directory(object):
    """Sets the cwd within the context

    Args:
        path (Path): The path to the cwd
        """
    def __init__(self, path: Path):
        self.path = path
        self.origin = Path().absolute()

    def __enter__(self):
        os.chdir(self.path)

    def __exit__(self, exc_type, exc_value, traceback):
        os.chdir(self.origin)


def save_image(image: SimpleITK.Image, name: str, is_label: bool = False):

    if is_label:
        output_img = SimpleITK.LabelToRGB(image)
    elif image.GetPixelID() in [SimpleITK.sitkUInt8, SimpleITK.sitkVectorUInt8]:
        output_img = image
    else:
        stats = SimpleITK.StatisticsImageFilter()
        stats.Execute(image)

        shift_scale = SimpleITK.ShiftScaleImageFilter()
        shift_scale.SetOutputPixelType(SimpleITK.sitkUInt8)
        shift_scale.SetShift(-stats.GetMinimum())
        shift_scale.SetScale(255.0/(stats.GetMaximum()-stats.GetMinimum()))

        output_img = shift_scale.Execute(image)

    SimpleITK.WriteImage(output_img, Path('..')/"images"/f"{name}.png")


def plot_image(image: SimpleITK.Image, cmap: str = 'gray'):
    """This takes a SimpleITK Image and plots it using Maptplotlib.

    This is needed for the Matplotlib Sphinx plot_directive so that
    images can be displayed in the documentation.

    :param image: image to be displayed
    :param cmap: optional ColorMap to use; defaults to 'gray'
    :return: None
    """

    size_pixels = image.GetSize()

    nda = SimpleITK.GetArrayFromImage(image)
    fig = plt.figure(figsize=(size_pixels[0]/DPI, size_pixels[1]/DPI), dpi=DPI)
    fig.figimage(nda, cmap=cmap)
    plt.show()


def run_example(module_name: str,
                func_name: str,
                args: list) -> dict:
    """Generic method of calling a SimpleITK Example 'main' routine

    Run the specified func_name on the module_name Example and
    pass it the provided args to it.

    :param module_name: name of the Example module
    :param func_name: name of the module_name function to call
    :param args: list of arguments to pass to func_name
    :return: A dictionary of keywords to Images
    """

    with set_directory(f"../../Examples/"):
        try:
            example_module = importlib.import_module(f"{module_name}.{module_name}")
        except (ImportError,) as ex:
            raise ValueError(f"Unknown module: {module_name}.{module_name} current directory {os.getcwd()}") from ex

        try:
            main_func = getattr(example_module, func_name)
        except AttributeError:
            raise RuntimeError(f"Unknown attribute: {func_name} in {example_module} --- {example_module.__path__}")

    args.insert(0, module_name)
    return_dict = main_func(args)

    return return_dict
