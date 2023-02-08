# gaussian_utils.py
# This utility file hides most of the Example-specific code. The main() routine
# now returns both the input and output SITK images so they can be displayed
# individually.
import SimpleITK
import matplotlib.pyplot as plt
import importlib

# The Matplotlib plot_directive dpi default for png
DPI = 80


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

    try:
        example_module = importlib.import_module(f"{module_name}.{module_name}")
    except (ImportError, AttributeError) as ex:
        raise ValueError(f"Unknown module: {module_name}") from ex

    main_func = getattr(example_module, func_name)
    args.insert(0, module_name)
    return_dict = main_func(args)
    return return_dict
