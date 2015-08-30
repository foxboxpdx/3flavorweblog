package WeblogDB;

use DBI;

sub new {
    my $class = shift;
    my $self = {
        _filename   => shift,
        _dbh        => undef,
    };
    $self->{_dbh} = DBI->connect("dbi:SQLite:dbname=$self->{_filename}","","");
    bless $self, $class;
    return $self;
}

sub write {
    my ($self, $log) = @_;
    my $query = sprintf "INSERT INTO weblogs (ipaddr, date, request, code, size, referer, agent) " .
                        "values (\"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\", \"%s\")",
                        $log->ipaddr, $log->date, $log->request, $log->code,
                        $log->size, $log->referer, $log->agent;
    $self->{_dbh}->do($query);
}

sub fetch {
    my ($self, $query) = @_;
    my @logarray;
    my $sth = $self->{_dbh}->prepare( "SELECT * FROM weblogs where $query" );
    $sth->execute();
    my $loghashes = $sth->fetchall_arrayref({});
    foreach my $log (keys $loghashes) {
        my $wl = new Weblog($log->{ipaddr}, $log->{date}, $log->{request},
                            $log->{code},   $log->{size}, $log->{referer},
                            $log->{agent});
        push(@logarray, $wl);
    }
    return @logarray;
}

sub fetch_all {
    my ($self, $limit) = @_;
    $limit = defined($limit) ? $limit : 50;
    my @logarray;
    my $sth = $self->{_dbh}->prepare( "SELECT * FROM weblogs LIMIT $limit" );
    $sth->execute();
    my $loghashes = $sth->fetchall_arrayref({});
    foreach my $log (keys $loghashes) {
        my $wl = new Weblog($log->{ipaddr}, $log->{date}, $log->{request},
                            $log->{code},   $log->{size}, $log->{referer},
                            $log->{agent});
        push(@logarray, $wl);
    }
    return @logarray;
}

sub create_tables {
    my ($self) = @_;
    my $create = "CREATE TABLE weblogs(" .
                 "ipaddr varchar(50) not null," .
                 "date varchar(50) not null," .
                 "request varchar(255) not null," .
                 "code int not null," .
                 "size int not null default 0," .
                 "referer varchar(255) not null," .
                 "agent varchar(255) not null, " .
                 "primary key (ipaddr, date) )";
    $self->{_dbh}->do($create);
}
1;
