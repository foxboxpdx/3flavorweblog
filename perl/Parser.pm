package Parser;

use Weblog;
use WeblogDB;

sub new {
    my $class = shift;
    my $self = {
        _database => shift,
        _logs     => [],
    };
    bless $self, $class;
    return $self;
}

sub getLogArray {
    my ($self) = @_;
    return $self->{_logs};
}

sub parseWeblog {
    my ($self, $line ) = @_;

    my $pattern =
      "(\\S+)\\s" . # IP Address
      "(\\S+)\\s" . # -
      "(\\S+)\\s" . # -
      "\\[(\\d{2}/\\w+/\\d{4}\\:\\d{2}\\:\\d{2}\\:\\d{2}\\s+.+?)\\]\\s" . # Date
      "\\\"(\\w+\\s\\S+\\s\\w+\\/\\d+\\.\\d+)\\\"\\s" . # Request
      "(\\d+)\\s" . # Code
      "(\\d+)\\s" . # Size
      "\\\"(\\S+)\\\"\\s" . # Referer
      "\\\"(.+)\\\"";  # Agent

    # Parse out the stuff we wants
    my ($ip, undef, undef, $date, $request, $code, $size, $referer, $agent) = $line =~ /$pattern/;

    return if (length($ip) < 1);
    # Make it a Weblog object
    my $weblog = new Weblog($ip, $date, $request, $code, $size, $referer, $agent);

    # Add to the logs array
    push ($self->{_logs}, $weblog);
}

sub count {
    my ($self) = @_;
    return length($self->{_logs});
}

sub toDatabase {
    my ($self) = @_;
    if (length($self->{_logs}) < 1) {
        return;
    }

    for my $log ($self->{_logs}) {
        $self->{_database}->write($log);
    }
}

sub toString {
    my ($self) = @_;
    if (length($self->{_logs}) < 1) { return; }

    for my $log (@{$self->{_logs}}) {
        print $log->to_string . "\n";
    }
}
1;
