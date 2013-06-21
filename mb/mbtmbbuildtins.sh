#!/bin/bash
glib-mkenums --template mbtmbtypebuildtins.c.template mbtmbenums.h > mbtmbtypebuildtins.c
glib-mkenums --template mbtmbtypebuildtins.h.template mbtmbenums.h > mbtmbtypebuildtins.h