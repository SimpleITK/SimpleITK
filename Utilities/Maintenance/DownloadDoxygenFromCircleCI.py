from circleci.api import Api
import re
import sys
import os


cci_username="SimpleITK"
cci_project="SimpleITK"
cci_branch="master"
cci_jobname="docs"
artifact_filename="simpleitk_doxygen_html.tar.gz"

circleci = Api(os.environ["CIRCLE_TOKEN"])

builds = circleci.get_project_build_summary(cci_username, cci_project, status_filter="successful", branch=cci_branch)

for bld in builds:
    if "workflows" in bld and bld["workflows"]["job_name"] == cci_jobname:
        break;

if bld["workflows"]["job_name"] != cci_jobname:
    sys.exit("Unable to locate a recent successful job_name:{0} build.")

artifacts_json = circleci.get_artifacts("SimpleITK", "SimpleITK", bld["build_num"])

for j in artifacts_json:
    if re.match(".*/{0}$".format(artifact_filename), j["path"]):
       break

if not re.match(".*/{0}$".format(artifact_filename), j["path"]):
    sys.exit("Unable to locate artifact:{0} in build:{1}".format(artifact_filename,  bld["build_num"]))

circleci.download_artifact(j["url"])
