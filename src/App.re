[@react.component]
let make = () => {
  open ReactBinding;
  let lazyHome =
    React.createElement(
      Lazy.lazy_(() =>
        Lazy.import_("./pages/Home.js")
        ->Js.Promise.then_(
            comp => Js.Promise.resolve({"default": comp##make}),
            _,
          )
      ),
      (),
    );

  let lazyAbout =
    React.createElement(
      Lazy.lazy_(() =>
        Lazy.import_("./pages/About.js")
        ->Js.Promise.then_(
            comp => Js.Promise.resolve({"default": comp##make}),
            _,
          )
      ),
      (),
    );

  let url = RescriptReactRouter.useUrl();
  let component =
    switch (url.path) {
    | [] => <SuspensionLoader> lazyHome </SuspensionLoader>
    | ["about"] => <SuspensionLoader> lazyAbout </SuspensionLoader>
    | _ => <NotFound />
    };

  let (theme, setTheme) = ThemeHook.useTheme("theme-blue");
  <ThemeSwitchProvider value=setTheme>
    <div className={j|$theme flex flex-col h-[100vh] dark:bg-slate-700 |j}>
      <NavBar />
      <ErrorBoundary>
        <div className="flex w-full h-full m-auto dark:bg-slate-700">
          component
        </div>
      </ErrorBoundary>
    </div>
  </ThemeSwitchProvider>;
};
