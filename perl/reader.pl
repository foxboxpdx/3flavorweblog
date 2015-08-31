#!/usr/bin/env perl
# Reader.pl
# Read in a specified file or dump out the specified number of records.
use strict;
use warnings;
use Parser;

my ($command, $param) = @ARGV;

if (not defined $command) {
  print "Usage:\n\t$0 parse <filename>\n\t$0 fetch <num records>\n";
  exit(1);
}

if ($command =~ /parse/) {
    if (not defined $param) {
        print "Usage:\n\t$0 parse <filename>\n\t$0 fetch <num records>\n";
        exit(1);
    }
    my $db = new WeblogDB("test.db");
    my $p = new Parser($db);
    print "Reading file: $param\n";
    open (SINK, "<$param");
    while (my $line = <SINK>) {
      $p->parseWeblog($line);
    }
    close SINK;
    print "Processed " . $p->count . " logs.\n";
    $p->toDatabase();
    print "Wrote to database ok.\n";
    exit(0);
} elsif ($command =~ /fetch/) {
    my $db = new WeblogDB("test.db");
    $param = 50 if (not defined $param);
    print "Fetching $param records from database...\n";
    my @logs = $db->fetch_all($param);
    foreach my $log (@logs) {
        print $log->to_string . "\n";
    }
} else {
    print "Usage:\n\t$0 parse <filename>\n\t$0 fetch <num records>\n";
    exit(1);
}

