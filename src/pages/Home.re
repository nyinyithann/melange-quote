module QuoteCard = {
  [@react.component]
  let make =
      (
        ~id,
        ~quote,
        ~author,
        ~contributer: option(QuoteModel.contributer)=?,
        ~setEdit,
      ) => {
    let controller = Fetch.AbortController.make();

    let delete = _ => {
      Data.deleteQuote(
        ~quoteId=id,
        ~abortSignal=Fetch.AbortController.signal(controller),
      );
    };

    <div
      className="flex flex-col items-start rounded shadow shadow-slate-200 border-[1px] gap-2 dark:text-white dark:border-slate-500 dark:shadow-slate-900 max-w-[30vw]">
      <p className="font-nav text-[1.2rem] p-2"> quote->React.string </p>
      {switch (author) {
       | Some(auth) =>
         <p className="font-brand p-2 pt-0">
           {("-- " ++ auth)->React.string}
         </p>
       | _ => React.null
       }}
      <div
        className="flex font-sans text-[0.8rem] rounded-b border-[1px] border-50 p-1 gap-2 w-full justify-end bg-300 divide-x divide-50">
        {switch (contributer) {
         | Some({name, _}) =>
           <p className="w-full py-1 px-2 text-sm rounded-b-sm text-left">
             {("Posted by: " ++ name)->React.string}
           </p>
         | _ => React.null
         }}
        <div
          className="flex items-center justify-center gap-1 text-900 underline px-1">
          <span className="cursor-pointer" onClick=delete>
            "Delete"->React.string
          </span>
          <span className="cursor-pointer" onClick={_ => setEdit(id)}>
            "Edit"->React.string
          </span>
        </div>
      </div>
    </div>;
  };
};

module QuoteForm = {
  [@react.component]
  let make = (~quoteToEdit: option(QuoteModel.quote)) => {
    let (quoteText, setQuoteText) = React.useState(_ => "");
    let (authorText, setAuthorText) = React.useState(_ => "");
    let idRef = React.useRef(Js.Int.min);

    React.useEffect1(
      () => {
        let (id, quote, author) =
          switch (quoteToEdit) {
          | Some(q) => (q.id, q.quote, q.author)
          | None => (Js.Int.min, "", None)
          };
        setQuoteText(_ => quote);
        setAuthorText(_ => Belt.Option.getWithDefault(author, ""));
        idRef.current = id;
        None;
      },
      [|quoteToEdit|],
    );

    let controller = Fetch.AbortController.make();
    let handleUpdate = e => {
      ReactEvent.Mouse.preventDefault(e);
      if (quoteText != "" && idRef.current != Js.Int.min) {
        let quote: QuoteModel.quote = {
          quote: quoteText,
          author: authorText == "" ? None : Some(authorText),
          contributerId: 1,
          id: idRef.current,
        };
        ();
        Data.updateQuote(
          ~quote,
          ~abortSignal=Fetch.AbortController.signal(controller),
        );
      };
    };

    let handleAdd = e => {
      ReactEvent.Mouse.preventDefault(e);
      if (quoteText != "") {
        let quote: QuoteModel.quote = {
          quote: quoteText,
          author: authorText == "" ? None : Some(authorText),
          contributerId: 1,
          id:0,
        };
        Data.addQuote(
          ~quote,
          ~abortSignal=Fetch.AbortController.signal(controller),
        );
      };
    };

    <div
      className="flex flex-col w-full itesm-center p-4 border-b-[2px] border-400 gap-2">
      <div className="flex items-start gap-4">
        <label
          htmlFor="quote-input" className="bg-200 p-2 rounded-r-full w-[6rem]">
          "Quote"->React.string
        </label>
        <textarea
          id="quote-input"
          required=true
          maxLength=1000
          value=quoteText
          onChange={e => {
            let value = ReactEvent.Form.target(e)##value;
            setQuoteText(_ => value);
          }}
          className="resize-none rounded w-full ring-0 outline-none active:ring-0 active:outline-none focus:ring-0 focus:outline-none border-transparent focus:border-transparent border-400 focus:border-400"
        />
      </div>
      <div className="flex items-start gap-4">
        <label
          htmlFor="author-input"
          className="bg-200 p-2 rounded-r-full w-[6rem]">
          "Author"->React.string
        </label>
        <input
          type_="text"
          id="author-input"
          value=authorText
          required=true
          maxLength=1000
          onChange={e => {
            let value = ReactEvent.Form.target(e)##value;
            setAuthorText(_ => value);
          }}
          className="resize-none rounded w-full ring-0 outline-none active:ring-0 active:outline-none focus:ring-0 focus:outline-none border-transparent focus:border-transparent border-400 focus:border-400"
        />
      </div>
      {switch (quoteToEdit) {
       | Some(_) =>
         <button
           type_="button"
           className="p-1 bg-400 text-800 w-[calc(100%-6.4rem)] rounded ml-auto"
           onClick=handleUpdate>
           "Update"->React.string
         </button>
       | None =>
         <button
           type_="button"
           className="p-1 bg-400 text-800 w-[calc(100%-6.4rem)] rounded ml-auto"
           onClick=handleAdd>
           "Add"->React.string
         </button>
       }}
    </div>;
  };
};

[@react.component]
let make = () => {
  let {loading, error, quotes}: QuoteStore.state =
    QuoteStore.store.useStore();

  let (quoteToEdit, setQuoteToEdit) = React.useState(_ => None);

  let controller = Fetch.AbortController.make();
  React.useEffect0(() => {
    Data.getQuotes(~abortSignal=Fetch.AbortController.signal(controller));
    Some(() => Fetch.AbortController.abort(controller));
  });


  let setEdit = id => {
    let quote = Belt.Array.getBy(quotes, x => x.id == id);
    switch (quote) {
    | Some(q) =>
      setQuoteToEdit(_ =>
        Some(
          {
            id: q.id,
            quote: q.quote,
            author: q.author,
            contributerId: q.contributer.id,
          }: QuoteModel.quote,
        )
      )
    | _ => ()
    };
  };

  if (Js.String.length(error) > 0) {
    <div className="pt-20"> error->React.string </div>;
  } else {
    <main
      className="flex flex-col w-[100vw] h-full justify-start items-start p-10 pt-20 gap-4">
      <div
        className={"text-center w-full" ++ (loading ? " visible" : " hidden")}>
        "loading..."->React.string
      </div>
      <QuoteForm quoteToEdit />
      <div
        className="flex flex-wrap w-full h-auto justify-start items-start gap-2">
        {Belt.Array.map(quotes, ({id, quote, author, contributer}) => {
           <QuoteCard
             key={Js.Int.toString(id)}
             id
             quote
             author
             contributer
             setEdit
           />
         })
         ->React.array}
      </div>
    </main>;
  };
};
