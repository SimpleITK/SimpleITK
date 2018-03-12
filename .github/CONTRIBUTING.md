
# Development

We welcome contributions from the community!

SimpleITK uses the [Git](http://git-scm.com/) distributed version control system. The main repository is hosted on [itk.org](https://itk.org/SimpleITK.git) and mirrored to [Github](https://github.com/SimpleITK/SimpleITK.git). We are currently using Github for pull requests, and issue tracking.

# Contribute

To submit code to SimpleITK, simply follow the standard GitHub workflow to make a pull request. More information can be found [here](https://guides.github.com/activities/forking/) and [here](https://gist.github.com/Chaser324/ce0505fbed06b947d962) regarding the workflow and getting your computer setup.

New feature topics should be based on the `master` branch, while bugs fixes for the recent release should be based on the `release` branch. A topic should *never* be based on the `next` branch.

## Setup

After cloning the repository, run `./Utilities/SetupForDevelopment.sh` from within the SimpleITK repository to setup Git hooks. Say "no" to setting up access to itk.org as only core developers need access for merging pull requests.

This setup script also sets up some alias for the legacy ITK's Gerrit review system.

## Branches

* **next** - An unstable branch which contains future features for testing. These will be tested nightly on [CDash](https://open.cdash.org/index.php?project=SimpleITK). If the tests pass, then they will be merged into master. Pull requests should never be based on this branch, however this is the default branch you should push changes to.
* **master** - Stable branch of the code and suitable for most users when building SimpleITK. New features should be based on this branch.
* **release** - Branch of the code from the stable release. Patches which are bug fixes for the most recent releae should be based on the `release` branch.

## Testing

Testing is very important for SimpleITK, to ensure quality and reliable code that "just works". Please include tests in pull request that add features or fix bugs.

Pull request will be reviewed and run through the continuous integration building and testing infrastructure to ensure quality code before being merged into the **next** branch for nightly testing.

The comprehensive regression testing is reported to the [CDash Dashboard](https://open.cdash.org/index.php?project=SimpleITK). This include the extensive nightly testing on the **next** branch, nightly distributions packages on the **release** or **master** branch, and continuous integration from Github pull requests.
