"""
downloaddata.py
===============

Download this file and Data folder and add them to your python path to run other
examples.

Since we do not want to store large binary data files in our Git repository,
we fetch_data_all from a network resource.

The data we download is described in a json file. The file format is a dictionary
of dictionaries. The top level key is the file name. The returned dictionary
contains an md5 checksum and possibly a url and boolean flag indicating
the file is part of an archive. The md5 checksum is mandatory.
When the optional url is given, we attempt to download from that url, otherwise
we attempt to download from the list of MIDAS servers returned by the 
get_midas_servers() function. Files that are contained in archives are
identified by the archive flag.

Example json file contents:

{
"SimpleITK.jpg": {
"md5sum": "2685660c4f50c5929516127aed9e5b1a"
},
"POPI/meta/00.mhd" : {
"md5sum": "3bfc3c92e18a8e6e8494482c44654fd3",
"url": "http://tux.creatis.insa-lyon.fr/~srit/POPI/Images/MetaImage/10-MetaImage.tar"
},
"CIRS057A_MR_CT_DICOM/readme.txt" : {
 "md5sum" : "d92c97e6fe6520cb5b1a50b96eb9eb96",
 "archive" : "true"
}
}

Notes: 
1. The file we download can be inside an archive. In this case, the md5 
checksum is that of the archive.

2. For the md5 verification to work we need to store archives on MIDAS and cannot
   use its on-the-fly archive download mechanism (this mechanism allows users
   to download "directories/communities" as a single zip archive). The issue is that
   every time the archive is created its md5 changes. It is likely MIDAS is also
   encoding the archive's modification/creation time as part of the md5.

   Another issue is that when downloading from this type of url 
   (e.g. http://midas3.kitware.com/midas/download/folder/11610/ipythonNotebookData.zip)
   the returned data does not have a "Content-Length" field in the header. The
   current implementation  will throw an exception.  
"""

import hashlib
import sys
import os
import json

import errno
import warnings

# http://stackoverflow.com/questions/2028517/python-urllib2-progress-hook

def url_download_report(bytes_so_far, url_download_size, total_size):
    percent = float(bytes_so_far) / total_size
    percent = round(percent * 100, 2)
    if bytes_so_far > url_download_size:
        # Note that the carriage return is at the begining of the
        # string and not the end. This accomodates usage in 
        # IPython usage notebooks. Otherwise the string is not
        # displayed in the output.
        sys.stdout.write("\rDownloaded %d of %d bytes (%0.2f%%)" %
                         (bytes_so_far, total_size, percent))
        sys.stdout.flush()
    if bytes_so_far >= total_size:
        sys.stdout.write("\rDownloaded %d of %d bytes (%0.2f%%)\n" %
                         (bytes_so_far, total_size, percent))
        sys.stdout.flush()
        
 
def url_download_read(url, outputfile, url_download_size=8192 * 2, report_hook=None):
    # Use the urllib2 to download the data. The Requests package, highly
    # recommended for this task, doesn't support the file scheme so we opted
    # for urllib2 which does.  

    try:
        # Python 3
        from urllib.request import urlopen, URLError, HTTPError
    except ImportError:
        from urllib2 import urlopen, URLError, HTTPError
    from xml.dom import minidom
    
    # Open the url
    try:
        url_response = urlopen(url)
    except HTTPError as e:
        return "HTTP Error: {0} {1}\n".format(e.code, url)
    except URLError as e:
        return "URL Error: {0} {1}\n".format(e.reason, url)
    # MIDAS is a service and therefor will not generate the expected URLError
    # when given a nonexistent url. It does return an error message in xml.
    # When the response is xml then we have an error, we read the whole message
    # and return the 'msg' attribute associated with the 'err' tag.
    # The URLError above is not superfluous as it will occur when the url 
    # refers to a non existent file ('file://non_existent_file_name') or url
    # which is not a service ('http://non_existent_address').    
    try:
        # Python 3
        content_type = url_response.info().get("Content-Type")
    except AttributeError:
        content_type = url_response.info().getheader("Content-Type")
    # MIDAS error message in json format
    if content_type == "text/html; charset=UTF-8":
        doc = json.loads(url_response.read().decode("utf-8"))
        if doc['stat']=='fail':
            return doc['message'] + url
    # MIDAS error message in xml format
    if content_type == "text/xml":
        doc = minidom.parseString(url_response.read())
        if doc.getElementsByTagName("err")[0]:
            return doc.getElementsByTagName("err")[0].getAttribute("msg") + ': ' + url
    # We download all content types - the assumption is that the md5sum ensures
    # that what we received is the expected data.
    try:
        # Python 3
        content_length = url_response.info().get("Content-Length")
    except AttributeError:
        content_length = url_response.info().getheader("Content-Length")
    total_size = content_length.strip()
    total_size = int(total_size)
    bytes_so_far = 0
    with open(outputfile, "wb") as local_file:
        while 1:
            try:
                url_download = url_response.read(url_download_size)
                bytes_so_far += len(url_download)
                if not url_download:
                    break
                local_file.write(url_download)
            # handle errors
            except HTTPError as e:
                return "HTTP Error: {0} {1}\n".format(e.code, url)
            except URLError as e:
                return "URL Error: {0} {1}\n".format(e.reason, url)
            if report_hook:
                report_hook(bytes_so_far, url_download_size, total_size)
    return "Downloaded Successfully"

# http://stackoverflow.com/questions/600268/mkdir-p-functionality-in-python?rq=1
def mkdir_p(path):
    try:
        os.makedirs(path)
    except OSError as exc:  # Python >2.5
        if exc.errno == errno.EEXIST and os.path.isdir(path):
            pass
        else:
            raise

#http://stackoverflow.com/questions/2536307/decorators-in-the-python-standard-lib-deprecated-specifically
def deprecated(func):
    """This is a decorator which can be used to mark functions
    as deprecated. It will result in a warning being emmitted
    when the function is used."""

    def new_func(*args, **kwargs):
        warnings.simplefilter('always', DeprecationWarning) #turn off filter 
        warnings.warn("Call to deprecated function {}.".format(func.__name__), category=DeprecationWarning, stacklevel=2)
        warnings.simplefilter('default', DeprecationWarning) #reset filter
        return func(*args, **kwargs)

    new_func.__name__ = func.__name__
    new_func.__doc__ = func.__doc__
    new_func.__dict__.update(func.__dict__)
    return new_func



def get_midas_servers():
    import os
    midas_servers = list()
    if 'ExternalData_OBJECT_STORES' in os.environ.keys():
        local_object_stores = os.environ['ExternalData_OBJECT_STORES']
        for local_object_store in local_object_stores.split(";"):
          midas_servers.append( "file://{0}/MD5/%(hash)".format(local_object_store) )
    midas_servers.extend( [
        # Data published by MIDAS
        "http://midas3.kitware.com/midas/api/rest?method=midas.bitstream.download&checksum=%(hash)&algorithm=%(algo)",
        # Data published by developers using git-gerrit-push.
        "http://www.itk.org/files/ExternalData/%(algo)/%(hash)",
        # Mirror supported by the Slicer community.
        "http://slicer.kitware.com/midas3/api/rest?method=midas.bitstream.download&checksum=%(hash)&algorithm=%(algo)",
        # Insight journal data server
        "http://www.insight-journal.org/midas/api/rest?method=midas.bitstream.by.hash&hash=%(hash)"
        ])
    return midas_servers


def output_hash_is_valid(known_md5sum, output_file):
    md5 = hashlib.md5()
    if not os.path.exists(output_file):
        return False
    with open(output_file, 'rb') as fp:
        for url_download in iter(lambda: fp.read(128 * md5.block_size), b''):
            md5.update(url_download)
    retreived_md5sum = md5.hexdigest()
    return retreived_md5sum == known_md5sum


def fetch_data_one(onefilename, output_directory, manifest_file, verify=True, force=False):
    import tarfile, zipfile
    
    with open(manifest_file, 'r') as fp:
        manifest = json.load(fp)
    assert onefilename in manifest, "ERROR: {0} does not exist in {1}".format(onefilename, manifest_file)

    sys.stdout.write("Fetching {0}\n".format(onefilename))
    output_file = os.path.realpath(os.path.join(output_directory, onefilename))
    data_dictionary = manifest[onefilename]
    md5sum = data_dictionary['md5sum']    
    # List of places where the file can be downloaded from
    all_urls = []    
    if "url" in data_dictionary:
        all_urls.append(data_dictionary["url"])    
    else:
        for url_base in get_midas_servers():
            all_urls.append(url_base.replace("%(hash)", md5sum).replace("%(algo)", "md5"))
        
    new_download = False

    for url in all_urls:
        # Only download if force is true or the file does not exist.
        if force or not os.path.exists(output_file):
            mkdir_p(os.path.dirname(output_file))
            # url_download_read(url, output_file, report_hook=url_download_report)
            url_download_read(url, output_file, report_hook=None)
            # Check if a file was downloaded and has the correct hash
            if output_hash_is_valid(md5sum, output_file):
                new_download = True
                # Stop looking once found
                break
            # If the file exists this means the hash is invalid we have a problem.
            elif os.path.exists(output_file):
                    error_msg = "File " + output_file
                    error_msg += " has incorrect hash value, " + md5sum + " was expected."
                    raise Exception(error_msg)

    # Did not find the file anywhere.        
    if not os.path.exists(output_file):
        error_msg = "File " + "\'"  + os.path.basename(output_file) +"\'"
        error_msg += " could not be found in any of the following locations:\n" 
        error_msg += ", ".join(all_urls)
        raise Exception(error_msg)
    
    if not new_download and verify:
        # If the file was part of an archive then we don't verify it. These
        # files are only verfied on download
        if ( not "archive" in data_dictionary) and ( not output_hash_is_valid(md5sum, output_file) ):
            # Attempt to download if md5sum is incorrect.
            fetch_data_one(onefilename, output_directory, manifest_file, verify, 
                           force=True)
    # If the file is in an archive, unpack it.                          
    if tarfile.is_tarfile(output_file) or zipfile.is_zipfile(output_file):
        tmp_output_file = output_file + ".tmp"
        os.rename(output_file, tmp_output_file)        
        if tarfile.is_tarfile(tmp_output_file):
            archive = tarfile.open(tmp_output_file)
        if zipfile.is_zipfile(tmp_output_file):
            archive = zipfile.ZipFile(tmp_output_file, 'r')
        archive.extractall(os.path.dirname(tmp_output_file))
        archive.close()
        os.remove(tmp_output_file)

    return output_file

@deprecated
def fetch_midas_data_one(onefilename, output_directory, manifest_file, verify=True, force=False):
    return fetch_data_one(onefilename, output_directory, manifest_file, verify, force)


def fetch_data_all(output_directory, manifest_file, verify=True):
    with open(manifest_file, 'r') as fp:
        manifest = json.load(fp)
    for filename in manifest:
        fetch_data_one(filename, output_directory, manifest_file, verify, 
                       force=False)

@deprecated
def fetch_midas_data_all(output_directory, manifest_file, verify=True):
    return fetch_data_all(output_directory, manifest_file, verify)


def fetch_data(cache_file_name, verify=False, cache_directory_name="Data"):
    """
    fetch_data is a simplified interface that requires
    relative pathing with a manifest.json file located in the
    same cache_directory_name name.

    By default the cache_directory_name is "Data" relative to the current
    python script.  An absolute path can also be given.
    """
    if not os.path.isabs(cache_directory_name):
        cache_root_directory_name = os.path.dirname(__file__)
        cache_directory_name = os.path.join(cache_root_directory_name, cache_directory_name)
    cache_manifest_file = os.path.join(cache_directory_name, 'manifest.json')
    assert os.path.exists(cache_manifest_file), "ERROR, {0} does not exist".format(cache_manifest_file)
    return fetch_data_one(cache_file_name, cache_directory_name, cache_manifest_file, verify=verify)

@deprecated
def fetch_midas_data(cache_file_name, verify=False, cache_directory_name="Data"):
    return fetch_data(cache_file_name, verify, cache_directory_name)


if __name__ == '__main__':
    
        
    if len(sys.argv) < 3:
        print('Usage: ' + sys.argv[0] + ' output_directory manifest.json')
        sys.exit(1)
    output_directory = sys.argv[1]
    if not os.path.exists(output_directory):
        os.makedirs(output_directory)
    manifest = sys.argv[2]
    fetch_data_all(output_directory, manifest)
