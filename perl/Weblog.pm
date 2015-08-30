package Weblog;

use overload
    '""' => 'to_string';

sub new {
    my $class = shift;
    my $self = {
        _ipaddr     => shift,
        _date       => shift,
        _request    => shift,
        _code       => shift,
        _size       => shift,
        _referer    => shift,
        _agent      => shift,
    };
    bless $self, $class;
    return $self;
}

sub to_string {
    my ($self) = @_;
    return sprintf "%-20s %-30s %-40s", $self->{_ipaddr}, $self->{_date}, $self->{_request};
}

sub ipaddr {
    my ($self) = @_;
    return $self->{_ipaddr};
}

sub date {
    my ($self) = @_;
    return $self->{_date};
}

sub request {
    my ($self) = @_;
    return $self->{_request};
}

sub code {
    my ($self) = @_;
    return $self->{_code};
}

sub size {
    my ($self) = @_;
    return $self->{_size};
}

sub referer {
    my ($self) = @_;
    return $self->{_referer};
}

sub agent {
    my ($self) = @_;
    return $self->{_agent};
}
1;
