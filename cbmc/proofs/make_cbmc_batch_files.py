#!/usr/bin/env python3
#
# Generation of the cbmc-batch.yaml files for the CBMC proofs.
#
# Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

import os
import platform
import subprocess
import logging

MAKEFILE = "Makefile"
YAML_FILE = "cbmc-batch.yaml"

def create_cbmc_yaml_files():
    # The YAML files are only used by CI and are not needed on Windows.
    if platform.system() == "Windows":
        return
    for dyr, _, files in os.walk("."):
        if YAML_FILE in files and MAKEFILE in files:
            logging.info("Building %s in %s", YAML_FILE, dyr)
            os.remove(os.path.join(os.path.abspath(dyr), YAML_FILE))
            subprocess.run(["make", YAML_FILE],
                           stdout=subprocess.PIPE,
                           stderr=subprocess.PIPE,
                           cwd=os.path.abspath(dyr),
                           check=True)

if __name__ == '__main__':
    create_cbmc_yaml_files()