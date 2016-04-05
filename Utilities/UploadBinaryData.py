#!/usr/bin/env python

from __future__ import print_function

description = """
Upload binary data to Midas.

Since every local Git repository contains a copy of the entire project history,
it is important to avoid adding large binary files directly to the repository.
Large binary files added and removed through the history of a project will cause
the repository to become bloated, take up too much disk space, require excessive
time and bandwidth to download, etc.

The solution to this problem adopted by this project is to store binary files,
such as images, in a separate location outside the repository, then download the
files at build time with CMake.

A "content link" file containing an identifying MD5 checksum is stored in the
Git repository at the path where the file would exist with the ".md5" extension
added to the file.  CMake will find these content link files at build time,
download them from a list of server resources, and create symlinks or copies of
the original files at the corresponding location in the build tree.

The Midas server at

  https://midas3.kitware.com/midas/

is an ITK community resource where any community member can upload binary data
files.  This script automates the upload of data to the server and generation of
the content link file.  Before using this script, please go to the Midas
website, register, and join the ITK community.

This script requires the Python module pydas:

    https://github.com/midasplatform/pydas

which can be installed with::

  pip install pydas

Pass in the input binary files to be uploaded. These should be files
located in the SimpleITK source tree. They will be uploaded and
replaced with a *.md5 file that can be added to the current
commit with "git add -- path/to/file.md5".
"""

import optparse
import hashlib
import os
import subprocess
import sys
import pydas


def connect_to_midas(email=None, api_key=None):
    midas_url = 'https://midas3.kitware.com/midas/'
    #pydas.login(url=midas_url, email=email, api_key=api_key)
    try:
        pydas.login(url=midas_url, email=email, api_key=api_key)
    except:
        print('Error occurred while logging in to ' + midas_url)
        sys.exit(1)
    session = pydas.session
    communicator = session.communicator
    return session, communicator


def upload_to_midas(input_file, output_file, folders, session, communicator):
    # get the MD5 checksum
    print('Computing MD5 checksum...')
    md5 = hashlib.md5()
    with open(input_file, 'rb') as fp:
        for chunk in iter(lambda: fp.read(128 * md5.block_size), b''):
            md5.update(chunk)
    md5hash = md5.hexdigest()
    print('Checksum: ' + md5hash)

    # upload to Midas
    def get_child_folder(parent, child_name):
        children = communicator.folder_children(session.token,
                                                parent['folder_id'])
        for folder in children['folders']:
            if folder['name'] == child_name:
                return folder
        return None
    itk_community = communicator.get_community_by_name('ITK')
    itk_public = get_child_folder(itk_community, 'Public')
    simpleitk = get_child_folder(itk_public, 'SimpleITK')

    current_folder = simpleitk
    for folder in folders:
        child_folder = get_child_folder(current_folder, folder)
        if child_folder is None:
            print('Creating folder: ' + folder)
            current_folder = \
                communicator.create_folder(session.token,
                                           folder,
                                           current_folder['folder_id'])
        else:
            current_folder = child_folder

    # get the existing or create a new item to hold the file
    item_name = os.path.basename(input_file)
    item_id = None
    current_folder_children = \
        communicator.folder_children(session.token,
                                     current_folder['folder_id'])
    if 'items' in current_folder_children:
        for item in current_folder_children['items']:
            if item['name'] == item_name:
                item_id = item['item_id']
                break

    if item_id is None:
        new_item = communicator.create_item(session.token, item_name,
                                            current_folder['folder_id'])
        item_id = new_item['item_id']

    upload_token = communicator.generate_upload_token(session.token,
                                                      item_id,
                                                      item_name,
                                                      md5hash)
    if upload_token != "":
        communicator.perform_upload(upload_token,
                                    item_name,
                                    item_id=item_id,
                                    revision='head',
                                    filepath=input_file)

    # write the content link file
    with open(output_file, 'w') as fp:
        fp.write(md5hash)
        fp.write('\n')


def find_git_dir(filepath):
    """Find our best estimate of GIT_DIR to locate the root of the SimpleITK
    repository."""
    filepath = os.path.abspath(filepath)
    head, tail = os.path.split(filepath)
    previous_head = ''
    while head != previous_head:
        if os.path.exists(os.path.join(head, '.git')):
            return head
        previous_head = head
        head, tail = os.path.split(head)
    print('Could not find the root of the SimpleITK repository!')
    sys.exit(1)


def run(input_files, output_files,
        email=None, api_key=None,
        no_delete=False):
    git_dir = find_git_dir(input_files[0])

    git_email_cmd = subprocess.Popen(['git', 'config', 'user.email'],
                                     cwd=git_dir,
                                     stdout=subprocess.PIPE)
    if git_email_cmd.wait() is 0:
        git_email = git_email_cmd.stdout.readline().strip()
        email_input = raw_input('Email [' + git_email + ']: ')
        if email_input == '':
            email = git_email
        else:
            email = email_input

    session, communicator = connect_to_midas(email, api_key)

    for ii in range(len(input_files)):
        input_abspath = os.path.abspath(input_files[ii])
        folders = input_abspath[len(git_dir)+1:].split(os.path.sep)[:-1]
        upload_to_midas(input_files[ii], output_files[ii], folders,
                        session, communicator)

        if not no_delete:
            os.remove(input_files[ii])


if __name__ == '__main__':
    usage = "%prog [options] input1 input2 ... inputN"
    parser = optparse.OptionParser(usage=usage)
    parser.add_option('--api-key-file', '-k', dest='api_key_file',
            help="A file that contains your Midas user's API key.")
    parser.add_option('--email', '-e',
            help="Email address associated with your Midas account.")
    parser.add_option('--no-delete', '-n', action='store_true',
            dest='no_delete',
            help='Do not remove the input files after upload.')
    (options, input_files) = parser.parse_args()

    if options.api_key_file:
        with open(options.api_key_file, 'r') as fp:
            api_key = fp.readline()
        api_key = api_key.strip()
    else:
        api_key = None

    output_files = []
    for ii in range(len(input_files)):
        output_files.append(input_files[ii] + '.md5')

    no_delete = options.no_delete

    run(input_files, output_files,
        email=options.email, api_key=api_key,
        no_delete=no_delete)
