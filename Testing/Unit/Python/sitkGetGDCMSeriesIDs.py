import SimpleITK as sitk
import unittest
import tempfile
import os
import shutil


class GDCMSeriesTest(unittest.TestCase):
    """Test the ImageSeriesReader_GetGDCMSeriesIDs method."""

    def setUp(self):
        self.test_dir = tempfile.mkdtemp()

    def tearDown(self):
        shutil.rmtree(self.test_dir)

    def _create_study_images(
        self, studyUID, number_of_series, number_images_per_series
    ):
        writer = sitk.ImageFileWriter()
        # Use the study/series/frame of reference information given in the meta-data
        # dictionary and not the automatically generated information from the file IO
        writer.KeepOriginalImageUIDOn()
        series_uids = []
        z_spacing = 0.5
        for i in range(number_of_series):
            seriesUID = "1.2.826.0.1.3680043.2.1125." + studyUID + str(i + 1) + ".1"
            series_uids.append(seriesUID)
            for j in range(number_images_per_series):
                instance_number = str(j + 1)
                image = sitk.Image([2, 2, 1], sitk.sitkInt16) + j
                image.SetOrigin([0, 0, j * z_spacing])
                image.SetMetaData("0020|000e", seriesUID)
                image.SetMetaData("0020,000d", studyUID)
                image.SetMetaData("0020|0013", instance_number)
                writer.SetFileName(
                    os.path.join(self.test_dir, f"{studyUID}_{seriesUID}_{j}.dcm")
                )
                writer.Execute(image)
        return series_uids

    @staticmethod
    def generate_test(number_of_studies, number_of_series, number_images_per_series):
        """Generate additional test by adding a generated member function"""

        def do_test(self):
            all_series = []
            for i in range(number_of_studies):
                all_series.extend(
                    self._create_study_images(
                        str(i + 1), number_of_series, number_images_per_series
                    )
                )
            # Use unittest.TestCase.assertCountEqual to compare the known list of series and
            # returned series UIDs. Function name is a bit misleading but docs say
            # "Test that sequence first contains the same elements as second,
            # regardless of their order."
            self.assertCountEqual(
                all_series, sitk.ImageSeriesReader.GetGDCMSeriesIDs(self.test_dir)
            )

        test_method = do_test
        test_method.__name__ = f"test_getgdcmseries_{number_of_studies}_{number_of_series}_{number_images_per_series}"
        setattr(GDCMSeriesTest, test_method.__name__, test_method)


# Programmatically generate tests (num_studies, num_series, num_images)
for config in [(0, 0, 0), (1, 1, 2), (1, 2, 2), (2, 1, 2), (3, 2, 3)]:
    GDCMSeriesTest.generate_test(*config)


if __name__ == "__main__":
    unittest.main()
