let getQuotes = (~abortSignal: Fetch.signal) => {
  let callback = result => {
    Belt.Result.(
      switch (result) {
      | Ok(data) =>
        switch (QuoteModel.Decode.decode_expanded_quotes(data)) {
        | Ok(items) => {
            Js.log(items);
          QuoteStore.store.dispatch(QuoteStore.LoadQuotes(items));
        }
        | Error(msg) => QuoteStore.store.dispatch(QuoteStore.Error(msg))
        }
      | Error(msg) => QuoteStore.store.dispatch(QuoteStore.Error(msg))
      }
    );
  };
  let apiPath = "/dev/quotes?_expand=contributer";
  [%debugger]
  QuoteStore.store.dispatch(Loading);
  Api.getQuotes(~apiPath, ~callback, ~signal=abortSignal, ());
};

let addQuote = (~quote: QuoteModel.quote, ~abortSignal: Fetch.signal) => {
  let callback = result => {
    Belt.Result.(
      switch (result) {
      | Ok(data) =>
        switch (QuoteModel.Decode.decode_quote(data)) {
        | Ok(item) => QuoteStore.store.dispatch(QuoteStore.AddQuote(item))
        | Error(msg) => QuoteStore.store.dispatch(QuoteStore.Error(msg))
        }
      | Error(msg) => QuoteStore.store.dispatch(QuoteStore.Error(msg))
      }
    );
  };
  let apiPath = "/dev/quotes";
  QuoteStore.store.dispatch(Loading);
  Api.postQuote(~apiPath, ~quote, ~callback, ~signal=abortSignal, ());
};

let deleteQuote = (~quoteId: int, ~abortSignal: Fetch.signal) => {
  let callback = result => {
    Belt.Result.(
      switch (result) {
      | Ok(_) => QuoteStore.store.dispatch(QuoteStore.DeleteQuote(quoteId))
      | Error(msg) => QuoteStore.store.dispatch(QuoteStore.Error(msg))
      }
    );
  };
  let apiPath = "/dev/quotes";
  QuoteStore.store.dispatch(Loading);
  Api.deleteQuote(~apiPath, ~quoteId, ~callback, ~signal=abortSignal, ());
};

let updateQuote = (~quote: QuoteModel.quote, ~abortSignal: Fetch.signal) => {
  let callback = result => {
    Belt.Result.(
      switch (result) {
      | Ok(data) =>
        switch (QuoteModel.Decode.decode_quote(data)) {
        | Ok(item) =>
          QuoteStore.store.dispatch(QuoteStore.UpdateQuote(item))
        | Error(msg) => QuoteStore.store.dispatch(QuoteStore.Error(msg))
        }
      | Error(msg) => QuoteStore.store.dispatch(QuoteStore.Error(msg))
      }
    );
  };
  let apiPath = "/dev/quotes";
  QuoteStore.store.dispatch(Loading);
  Api.putQuote(~apiPath, ~quote, ~callback, ~signal=abortSignal, ());
};
