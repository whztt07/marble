#
# This file is part of the Marble Virtual Globe.  
#
# This program is free software licensed under the GNU LGPL. You can
# find a copy of this license in LICENSE.txt in the top directory of
# the source code.
#
# Copyright 2012 Rene Kuettner <rene@bitkanal.net>
#

from __future__ import print_function

from SpaceObject import SpaceObject

class ObjectCatalogue(object):

    def __init__(self, filename, baseURL):
        super(ObjectCatalogue, self).__init__()
        self._filename = filename;
        self._baseURL = baseURL
        self._file = None
        self._open()

    def __del__(self):
        self._close()

    def add(self, space_obj, latest_vector):
        url = self._baseURL + "/" + space_obj.filename_prefix + '.txt'
        if(space_obj.mission_end is None):
            missionEnd = ''
        if(space_obj.mission_start is None):
            mission_start = ''
        self._file.write(', '.join([
            space_obj.name,
            space_obj.related_body,
            str(space_obj.mission_start),
            str(space_obj.mission_end),
            url
            ] + [str(x) for x in latest_vector]) + "\n")
        print(space_obj.name + " added to object catalogue.")

    def _open(self):
        self._file = open(self._filename, 'w+')
        self._file.truncate()
        self._file.write('# name, related_body, mission_start, '+
            'mission_end, url, <...latest state vector...>\n')

    def _close(self):
        self._file.close()
 
