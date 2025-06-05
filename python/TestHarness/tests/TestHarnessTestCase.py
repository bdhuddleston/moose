#* This file is part of the MOOSE framework
#* https://mooseframework.inl.gov
#*
#* All rights reserved, see COPYRIGHT for full restrictions
#* https://github.com/idaholab/moose/blob/master/COPYRIGHT
#*
#* Licensed under LGPL 2.1, please see LICENSE for details
#* https://www.gnu.org/licenses/lgpl-2.1.html

import os
import unittest
import subprocess
import tempfile
import re
import json
from contextlib import nullcontext

class TestHarnessTestCase(unittest.TestCase):
    """
    TestCase class for running TestHarness commands.
    """

    def runTests(self, *args, tmp_output=True, as_json=False, no_capabilities=True):
        cmd = ['./run_tests'] + list(args) + ['--term-format', 'njCst']
        if no_capabilities:
            cmd += ['--no-capabilities']
        sp_kwargs = {'cwd': os.path.join(os.getenv('MOOSE_DIR'), 'test'),
                     'text': True}
        context = tempfile.TemporaryDirectory if tmp_output else nullcontext
        output = None
        with context() as c:
            if tmp_output:
                cmd += ['-o', c]
            try:
                output = subprocess.check_output(cmd, **sp_kwargs)
            except subprocess.CalledProcessError:
                if not as_json:
                    raise
            if as_json:
                with open(os.path.join(c, '.previous_test_results.json'), 'r') as f:
                    return json.loads(f.read())
            else:
                return output

    def runExceptionTests(self, *args, tmp_output=True):
        try:
            self.runTests(*args, tmp_output=tmp_output)
        except Exception as err:
            return err.output
        raise RuntimeError('test failed to fail')

    def checkStatus(self, output, passed=0, skipped=0, pending=0, failed=0):
        """
        Make sure the TestHarness status line reports the correct counts.
        """
        # We need to be sure to match any of the terminal codes in the line
        status_re = r'(?P<passed>\d+) passed.*, .*(?P<skipped>\d+) skipped.*, .*(?P<failed>\d+) failed'
        match = re.search(status_re, output, re.IGNORECASE)
        self.assertNotEqual(match, None)
        self.assertEqual(match.group("passed"), str(passed))
        self.assertEqual(match.group("failed"), str(failed))
        self.assertEqual(match.group("skipped"), str(skipped))
