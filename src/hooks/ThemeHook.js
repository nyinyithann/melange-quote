// Generated by Melange

import * as Curry from "melange/lib/es6/curry.mjs";
import * as React from "react";
import * as Js_exn from "melange/lib/es6/js_exn.mjs";
import * as Caml_js_exceptions from "melange/lib/es6/caml_js_exceptions.mjs";

var themeKey = "Melange_React_Theme";

function useTheme(defaultTheme) {
  var match = React.useState(function () {
        try {
          var v = localStorage.getItem(themeKey);
          if (v !== null) {
            return v;
          } else {
            return defaultTheme;
          }
        }
        catch (exn){
          return defaultTheme;
        }
      });
  var setStoredTheme = match[1];
  var setTheme = function (themeName) {
    try {
      localStorage.setItem(themeKey, themeName);
      Curry._1(setStoredTheme, (function (_prev) {
              return themeName;
            }));
      return ;
    }
    catch (raw_e){
      var e = Caml_js_exceptions.internalToOCamlException(raw_e);
      if (e.RE_EXN_ID === Js_exn.$$Error) {
        var msg = e._1.message;
        if (msg !== undefined) {
          console.log(msg);
          return ;
        } else {
          return ;
        }
      }
      throw e;
    }
  };
  return [
          match[0],
          setTheme
        ];
}

export {
  themeKey ,
  useTheme ,
}
/* react Not a pure module */
