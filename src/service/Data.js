// Generated by Melange

import * as Api from "./Api.js";
import * as Curry from "melange/lib/es6/curry.mjs";
import * as QuoteModel from "../model/QuoteModel.js";
import * as QuoteStore from "../store/QuoteStore.js";

function getQuotes(abortSignal) {
  var callback = function (result) {
    if (result.TAG !== /* Ok */0) {
      return Curry._1(QuoteStore.store.dispatch, {
                  TAG: /* Error */4,
                  _0: result._0
                });
    }
    var items = QuoteModel.Decode.decode_expanded_quotes(result._0);
    if (items.TAG !== /* Ok */0) {
      return Curry._1(QuoteStore.store.dispatch, {
                  TAG: /* Error */4,
                  _0: items._0
                });
    }
    var items$1 = items._0;
    console.log(items$1);
    Curry._1(QuoteStore.store.dispatch, {
          TAG: /* LoadQuotes */3,
          _0: items$1
        });
  };
  debugger;
  Curry._1(QuoteStore.store.dispatch, /* Loading */0);
  Api.getQuotes("/dev/quotes?_expand=contributer", callback, abortSignal, undefined);
}

function addQuote(quote, abortSignal) {
  var callback = function (result) {
    if (result.TAG !== /* Ok */0) {
      return Curry._1(QuoteStore.store.dispatch, {
                  TAG: /* Error */4,
                  _0: result._0
                });
    }
    var item = QuoteModel.Decode.decode_quote(result._0);
    if (item.TAG === /* Ok */0) {
      return Curry._1(QuoteStore.store.dispatch, {
                  TAG: /* AddQuote */0,
                  _0: item._0
                });
    } else {
      return Curry._1(QuoteStore.store.dispatch, {
                  TAG: /* Error */4,
                  _0: item._0
                });
    }
  };
  Curry._1(QuoteStore.store.dispatch, /* Loading */0);
  Api.postQuote("/dev/quotes", quote, callback, abortSignal, undefined);
}

function deleteQuote(quoteId, abortSignal) {
  var callback = function (result) {
    if (result.TAG === /* Ok */0) {
      return Curry._1(QuoteStore.store.dispatch, {
                  TAG: /* DeleteQuote */1,
                  _0: quoteId
                });
    } else {
      return Curry._1(QuoteStore.store.dispatch, {
                  TAG: /* Error */4,
                  _0: result._0
                });
    }
  };
  Curry._1(QuoteStore.store.dispatch, /* Loading */0);
  Api.deleteQuote("/dev/quotes", quoteId, callback, abortSignal, undefined);
}

function updateQuote(quote, abortSignal) {
  var callback = function (result) {
    if (result.TAG !== /* Ok */0) {
      return Curry._1(QuoteStore.store.dispatch, {
                  TAG: /* Error */4,
                  _0: result._0
                });
    }
    var item = QuoteModel.Decode.decode_quote(result._0);
    if (item.TAG === /* Ok */0) {
      return Curry._1(QuoteStore.store.dispatch, {
                  TAG: /* UpdateQuote */2,
                  _0: item._0
                });
    } else {
      return Curry._1(QuoteStore.store.dispatch, {
                  TAG: /* Error */4,
                  _0: item._0
                });
    }
  };
  Curry._1(QuoteStore.store.dispatch, /* Loading */0);
  Api.putQuote("/dev/quotes", quote, callback, abortSignal, undefined);
}

export {
  getQuotes ,
  addQuote ,
  deleteQuote ,
  updateQuote ,
}
/* QuoteStore Not a pure module */
