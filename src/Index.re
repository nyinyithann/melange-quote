%raw
{|import "../style/main.css"|};

ReactDOM.querySelector("#root")
->(
    fun
    | Some(rootElm) => {
        let root = ReactBinding.createRoot(rootElm);
        ReactBinding.Root.render(
          root,
          <App />,
          /* 
             1. StrictMode will mount components 2 times, and there will be double-fetch
             2. Worst is cancelling data fetch in useEffect if abort is called in clenup function. 
             React 17 doesn't have No. 2 issue. react 18 has both.
          */
          /* <React.StrictMode> <App /> </React.StrictMode>, */
        );
      }
    | None =>
      Js.Console.error(
        "Failed to start React: couldn't find the #root element",
      )
  );
