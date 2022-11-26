module Root = {
  type t;

  [@bs.send] external render: (t, React.element) => unit = "render";
};

[@bs.module "react-dom/client"]
external createRoot: Dom.element => Root.t = "createRoot";

module Suspense = {
  [@bs.module "react"] [@react.component]
  external make:
    (~fallback: React.element, ~children: React.element, unit) => React.element =
    "Suspense";
};

module Lazy = {
  [@bs.val]
  external import_: string => Js.Promise.t({. "make": React.component(unit)}) =
    "import";

  [@bs.module "react"]
  external lazy_:
    (unit => Js.Promise.t({. "default": React.component(unit)})) =>
    React.component(unit) =
    "lazy";
};
