module Menu = {
  type menuRenderPropArg = {
    [@bs.as "open"]
    open_: bool,
  };

  [@bs.module "@headlessui/react"] [@react.component]
  external make:
    (
      ~as_: string=?,
      ~children: menuRenderPropArg => React.element,
      ~className: string=?
    ) =>
    React.element =
    "Menu";

  module Button = {
    [@bs.module "@headlessui/react"] [@bs.scope "Menu"] [@react.component]
    external make:
      (~as_: string=?, ~children: React.element=?, ~className: string=?) =>
      React.element =
      "Button";
  };

  module Items = {
    [@bs.module "@headlessui/react"] [@bs.scope "Menu"] [@react.component]
    external make:
      (
        ~as_: string=?,
        ~children: React.element=?,
        ~className: string=?,
        ~static: bool=?
      ) =>
      React.element =
      "Items";
  };

  module Item = {
    type itemRenderPropArg = {
      active: bool,
      disabled: bool,
    };
    [@bs.module "@headlessui/react"] [@bs.scope "Menu"] [@react.component]
    external make:
      (
        ~as_: string=?,
        ~children: itemRenderPropArg => React.element,
        ~className: string=?
      ) =>
      React.element =
      "Item";
  };
};
