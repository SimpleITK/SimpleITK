# Contributing to SimpleITK

We welcome contributions from the community!

SimpleITK uses the [Git](http://git-scm.com/) distributed version control system. The main repository is hosted on [Github](https://github.com/SimpleITK/SimpleITK.git) and the [Insight Software Consortium](https://github.com/InsightSoftwareConsortium/SimpleITK). For pull requests and issue tracking  Github is also used.

There are many ways to contribute to SimpleITK:
 - Report Bugs and Issues
 - Improve SimpleITK Examples and Documentation
 - Request new features
 - Enhance the code coverage
 - Contribute code to fix bugs or add new features.

## Setup for development

The following documentation is for an advanced contributor who is already familiar with git and GitHub workflow. The [ITK](https://github.com/InsightSoftwareConsortium/ITK) documentation may provide more details, or many online resource can orient you.

After you have cloned and forked the SimpleITK repository run the following command from the root:
```
./Utilities/SetupForDevelopment.sh
```

This script will configure your local checkout with the `upstream` repository and your own fork. Additionally, local hooks and aliases are added.

## Workflow

Submitting code to SimpleITK follows the standard pull request GitHub workflow. More information can be found [here](https://guides.github.com/activities/forking/) and [here](https://guides.github.com/introduction/flow/) regarding the workflow and getting your computer setup.

SimpleITK uses a branchy workflow where each PR should be a new topic branch. Locally, you create a branch with a concise and precise name then commit your changes to that branch. The branch should be based on your target branch which will usually be `master` for new features and improvements or `release` for back patches such as bugs fixes.

After completing the local branch, push it to your fork, then create a GitHub pull request in the SimpleITK upstream repository. The pull request is then required to have an approving *code review*, and the *continuous integration* testing pass before the topic is merged into the upstream repository.

### How to contribute with the right workflow using github commands

1. Setup
Fork the repo
https://github.com/SimpleITK/SimpleITK.git

clone to your laptop
``` shell
git clone https://github.com/<username>/SimpleITK.git
```
Go to the folder
``` shell
cd SimpleITK
```
Check the repo
```shell
git remote -v
origin  https://github.com/<username>/SimpleITK.git (fetch)
origin  https://github.com/<username>/SimpleITK.git (push)
```
Add the upstream
``` shell
git remote add upstream https://github.com/SimpleITK/SimpleITK.git
```
Check the repos again
```shell
git remote -v
origin  https://github.com/<username>/SimpleITK.git (fetch)
origin  https://github.com/<username>/SimpleITK.git (push)
upstream        https://github.com/SimpleITK/SimpleITK.git (fetch)
upstream        https://github.com/SimpleITK/SimpleITK.git (push)
```
Download the upstream repo in to your local
``` shell
git fetch upstream
```
You will see something like this:
``` shell
 * [new branch]        dashboard  -> upstream/dashboard
 * [new branch]        master     -> upstream/master
 * [new branch]        release    -> upstream/release
```
2. Start a branch
Create your new branch where "newdocumentation" is the name of the new branch. you can change the name
``` shell
git checkout -b newdocumentation upstream/master
Branch 'newdocumentation' set up to track remote branch 'master' from 'upstream'.
Switched to a new branch 'newdocumentation'
```
To check the branches to type this:
``` shell
git branch
```
The name with the * in front is the branch that you are.
``` shell
  master
* newdocumentation
```
3. Create a Pull Request
Work on the project and when you are done save the files and add, commit and push to origin
``` shell
git status
git add .
git commit -m"a new commit"
git push origin
```
Once you push it go to your fork repo
``` shell
<username>/SimpleITK
```
Click on the green button name "compare & pull request" and submit your pull request

4. Update a Pull Request
 When you update your Pull Request you save the files and add, commit and push to origin.
 ``` shell
git status
git add .
git commit -m"a new commit"
git push origin
```
Once you push it go to your fork repo
``` shell
<username>/SimpleITK
```
You will not see again the green button name "compare & pull request". That mean that your request have been update it. You can now go to your pull request (PR) in the https://github.com/SimpleITK/SimpleITK.git and click in the pull request tab, then click on your PR and check the comments and more.

## Branches

* **master** - Stable branch of the code which is expected to available to users when building SimpleITK. New features should be based on this branch.
* **release** - Branch of the code from the stable release. Patches which are bug fixes for the most recent release should be based on the `release` branch.
* **dashboard** - CMake scripts used for continuous integration and nightly testing

## Testing

Testing is very important for SimpleITK, to ensure quality and reliable code that "just works". Please include tests in pull request that add features or fix bugs.

Pull requests are run through the continuous integration building and
testing infrastructure to ensure quality code. Many options are tested
on the PR, but more are run when merged into master. It is important
to check the [CDash Dashboard](https://open.cdash.org/index.php?project=SimpleITK) to verify no new warnings or regression test failures are introduced after your patch has been merged.

The regression testing is reported to the [CDash Dashboard](https://open.cdash.org/index.php?project=SimpleITK).
