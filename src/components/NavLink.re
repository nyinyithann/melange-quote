[@react.component]
let make = (~to_, ~children) => {
  let url = RescriptReactRouter.useUrl();
  let path =
    switch (url.path) {
    | [] => "/"
    | _ =>
      let path = Belt.List.reduce(url.path, "", (acc, p) => acc ++ "/" ++ p);
      let re = Js.Re.fromString("/\/$/g");
      Js.String.replaceByRe(re, "", path);
    };

  let baseStyle = "focus:outline-none h-8 rounded-sm hover:bg-400/60 dark:hover:bg-slate-500 px-3 text-900";
  let className =
    path == to_ ? {j| $baseStyle bg-400/60 dark:bg-slate-500 |j} : baseStyle;

  <button
    type_="button"
    className
    onClick={e => {
      ReactEvent.Mouse.preventDefault(e);
      RescriptReactRouter.push(to_);
    }}>
    children
  </button>;
};
