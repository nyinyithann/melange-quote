type contributer = {
  id: int,
  name: string,
};

type quote = {
  id: int,
  quote: string,
  author: option(string),
  contributerId: int,
};

type expanded_quote = {
  id: int,
  quote: string,
  author: option(string),
  contributer,
};

type expanded_quotes = {items: array(expanded_quote)};

module Decode = {
  let contributer = json =>
    Json.Decode.{
      id: json |> field("id", int),
      name: json |> field("name", string),
    };

  let quote = json => {
    Json.Decode.{
      id: json |> field("id", int),
      quote: json |> field("quote", string),
      author: json |> optional(field("author", string)),
      contributerId: json |> field("contributerId", int),
    };
  };

  let expanded_quote = json => {
    Json.Decode.{
      id: json |> field("id", int),
      quote: json |> field("quote", string),
      author: json |> optional(field("author", string)),
      contributer: json |> field("contributer", contributer),
    };
  };

  let expanded_quotes = json => {
    Json.Decode.{items: json |> array(expanded_quote)};
  };

  let decode_quote = (json: Js.Json.t) => {
    Belt.Result.(
      try(Ok(quote(json))) {
      | Json.Decode.DecodeError(msg) => Error(msg)
      }
    );
  };
  
  let decode_expanded_quote = (json: Js.Json.t) => {
    Belt.Result.(
      try(Ok(expanded_quote(json))) {
      | Json.Decode.DecodeError(msg) => Error(msg)
      }
    );
  };

  let decode_expanded_quotes = (json: Js.Json.t) => {
    Belt.Result.(
      try(Ok(expanded_quotes(json))) {
      | Json.Decode.DecodeError(msg) => Error(msg)
      }
    );
  };
};

module Encode = {
  let encode = (q: quote) => {
    open Json.Encode;
    let props = [
      ("id", int(q.id)),
      ("quote", string(q.quote)),
      (
        "author",
        switch (q.author) {
        | Some(a) => string(a)
        | None => null
        },
      ),
      ("contributerId", int(q.contributerId)),
    ];

    object_(props);
  };
};
