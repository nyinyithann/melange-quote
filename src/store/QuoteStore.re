type state = {
  loading: bool,
  error: string,
  quotes: array(QuoteModel.expanded_quote),
};

let initialState = {loading: false, error: "", quotes: [||]};

type action =
  | AddQuote(QuoteModel.quote)
  | DeleteQuote(int)
  | UpdateQuote(QuoteModel.quote)
  | LoadQuotes(QuoteModel.expanded_quotes)
  | Loading
  | Error(string);

let add = (quote: QuoteModel.quote, state) => {
  Belt.Array.push(
    state.quotes,
    {
      id: quote.id,
      quote: quote.quote,
      author: quote.author,
      contributer: {
        id: quote.contributerId,
        name: "",
      } // json-server cannot return expand model when add new..so just fake it
    },
  );
  {loading: false, error: "", quotes: state.quotes};
};

let delete = (id, state) => {
  loading: false,
  error: "",
  quotes: Belt.Array.keep(state.quotes, x => x.id != id),
};

let update = (quote: QuoteModel.quote, state) => {
  let i = Belt.Array.getIndexBy(state.quotes, x => x.id == quote.id);
  switch (i) {
  | Some(j) =>
    state.quotes[j] = {
      id: quote.id,
      quote: quote.quote,
      author: quote.author,
      contributer: {
        id: quote.contributerId,
        name: "",
      } // json-server cannot return expand model when add new
    }
  | None => ()
  };
  {loading: false, error: "", quotes: state.quotes};
};

let load = (quotes: QuoteModel.expanded_quotes) => {
  loading: false,
  error: "",
  quotes: quotes.items,
};

let reducer = (state: state, action: action) => {
  switch (action) {
  | AddQuote(quote) => add(quote, state)
  | DeleteQuote(id) => delete(id, state)
  | UpdateQuote(quote) => update(quote, state)
  | LoadQuotes(quotes) => load(quotes)
  | Loading => {...state, loading: true}
  | Error(error) => {...state, error}
  };
};

let store = Restorative.createStore(initialState, reducer);
