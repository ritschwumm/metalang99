#!/bin/bash

echo "compare_25_items.h"
time gcc bench/compare_25_items.h -ftrack-macro-expansion=0 -Iinclude

echo ""
echo "list_of_100_items.h"
time gcc bench/list_of_100_items.h -ftrack-macro-expansion=0 -Iinclude

echo ""
echo "100_v.h"
time gcc bench/100_v.h -ftrack-macro-expansion=0 -Iinclude

echo ""
echo "100_call.h"
time gcc bench/100_call.h -ftrack-macro-expansion=0 -Iinclude

echo ""
echo "many_call_in_arg_pos.h"
time gcc bench/many_call_in_arg_pos.h -ftrack-macro-expansion=0 -Iinclude
