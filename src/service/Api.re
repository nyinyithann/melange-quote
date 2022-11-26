open Fetch;
open Js.Promise;

let contentType = ("Content-type", "application/json");

let handleResponse = promise =>
  promise
  |> then_(response =>
       if (Response.ok(response)) {
         Belt.Result.Ok(Response.json(response)) |> resolve;
       } else {
         [%debugger];
         Belt.Result.Error(Response.statusText(response)) |> resolve;
       }
     );

let handleFault = promise =>
  promise
  |> catch(_ => Belt.Result.Error("unexpected promise fault") |> resolve);

let handleResult = (callback, promise) =>
  promise
  |> then_(result =>
       switch (result) {
       | Belt.Result.Ok(p) =>
         p
         |> Js.Promise.then_(data => {
              callback(Belt.Result.Ok(data));
              resolve();
            })
       | Belt.Result.Error(msg) =>
         callback(Belt.Result.Error(msg));
         resolve();
       }
     );

let getQuotes =
    (
      ~apiPath: string,
      ~callback: result(Js.Json.t, string) => unit,
      ~signal,
      (),
    ) => {
  let requestInit =
    Fetch.RequestInit.make(
      ~method_=Get,
      ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
      ~signal,
      (),
    );

  Fetch.fetchWithInit(apiPath, requestInit)
  |> handleResponse
  |> handleFault
  |> handleResult(callback)
  |> ignore;
};

let postQuote =
    (
      ~apiPath: string,
      ~quote: QuoteModel.quote,
      ~callback: result(Js.Json.t, string) => unit,
      ~signal,
      (),
    ) => {
  let requestInit =
    Fetch.RequestInit.make(
      ~method_=Post,
      ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
      ~body=
        Fetch.BodyInit.make(
          quote |> QuoteModel.Encode.encode |> Js.Json.stringify,
        ),
      ~signal,
      (),
    );
  Fetch.fetchWithInit(apiPath, requestInit)
  |> handleResponse
  |> handleFault
  |> handleResult(callback)
  |> ignore;
};

let deleteQuote =
    (
      ~apiPath: string,
      ~quoteId: int,
      ~callback: result(Js.Json.t, string) => unit,
      ~signal,
      (),
    ) => {
  let requestInit =
    Fetch.RequestInit.make(
      ~method_=Delete,
      ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
      ~signal,
      (),
    );
  Fetch.fetchWithInit(
    apiPath ++ "/" ++ Js.Int.toString(quoteId),
    requestInit,
  )
  |> handleResponse
  |> handleFault
  |> handleResult(callback)
  |> ignore;
};

let putQuote =
    (
      ~apiPath: string,
      ~quote: QuoteModel.quote,
      ~callback: result(Js.Json.t, string) => unit,
      ~signal,
      (),
    ) => {
  let requestInit =
    Fetch.RequestInit.make(
      ~method_=Put,
      ~headers=Fetch.HeadersInit.make({"Content-Type": "application/json"}),
      ~body=
        Fetch.BodyInit.make(
          quote |> QuoteModel.Encode.encode |> Js.Json.stringify,
        ),
      ~signal,
      (),
    );
  Fetch.fetchWithInit(
    apiPath ++ "/" ++ Js.Int.toString(quote.id),
    requestInit,
  )
  |> handleResponse
  |> handleFault
  |> handleResult(callback)
  |> ignore;
};
