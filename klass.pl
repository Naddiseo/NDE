#!/usr/bin/perl

use strict;
use warnings;
use 5.10.0;

my ($folder, $name) = @ARGV;

my $hpp_path = "./$folder/$name\.hpp";
my $cpp_path = "./$folder/$name\.cpp";

if (-f $hpp_path || -f $cpp_path) {
	say "Class exists";
	exit;
}

open my $hpp, '>', $hpp_path or die $!;
open my $cpp, '>', $cpp_path or die $!;


say $hpp <<EOF;
#pragma once

namespace nde {

class $name {
public:
	$name\();
	virtual ~$name\();
};

} // namespace nde

EOF

say $cpp <<EOF;
#include "$folder/$name\.hpp"

namespace nde {

$name\::$name\() {}

$name\::~$name\() {}

} // namespace nde
EOF
