#!/usr/bin/perl -w
use strict;
use Parser;

my $db = new WeblogDB("test.db");
my $p = new Parser($db);

open (SINK, "<short.log");
my @lines = <SINK>;
close SINK;

foreach my $line (@lines) {
    $p->parseWeblog($line);
}

$p->toString
