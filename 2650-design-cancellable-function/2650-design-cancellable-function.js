function cancellable(generator) {
  let cancelled = false;
  let done = false;
  let cancelFn;

  const promise = new Promise((resolve, reject) => {
    function step(input, isError) {
      if (done) return;
      let result;
      try {
        result = isError ? generator.throw(input) : generator.next(input);
      } catch (err) {
        done = true;
        reject(err);
        return;
      }

      if (result.done) {
        done = true;
        resolve(result.value);
        return;
      }

      if (cancelled) {
        step("Cancelled", true);
        return;
      }

      let settled = false;
      cancelFn = () => {
        if (settled) return;
        settled = true;
        step("Cancelled", true);
      };

      result.value.then(
        (val) => {
          if (settled) return;
          settled = true;
          step(val, false);
        },
        (err) => {
          if (settled) return;
          settled = true;
          step(err, true);
        }
      );
    }

    step(undefined, false);
  });

  const cancel = () => {
    if (cancelled || done) return;
    cancelled = true;
    if (cancelFn) cancelFn();
  };

  return [cancel, promise];
}