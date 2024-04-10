import SimpleITK
import importlib

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
        shift_scale.SetScale(255.0 / (stats.GetMaximum() - stats.GetMinimum()))

        output_img = shift_scale.Execute(image)

    SimpleITK.WriteImage(output_img, Path("..") / "images" / f"{name}.png")


def run_example(module_name: str, func_name: str, args: list) -> dict:
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
            raise ValueError(
                f"Unknown module: {module_name}.{module_name} current directory {os.getcwd()}"
            ) from ex

        try:
            main_func = getattr(example_module, func_name)
        except AttributeError:
            raise RuntimeError(
                f"Unknown attribute: {func_name} in {example_module} --- {example_module.__path__}"
            )

    args.insert(0, module_name)
    return_dict = main_func(args)

    return return_dict
