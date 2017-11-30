table! {
    weblogs (ipaddr, date) {
        ipaddr -> Text,
        date -> Text,
        request -> Text,
        code -> Integer,
        size -> Integer,
        referer -> Text,
        agent -> Text,
    }
}
