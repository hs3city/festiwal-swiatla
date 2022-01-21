(function () {
  const targetDate = moment("2022-05-13 18:00 +0100", "YYYY-MM-DD HH:mm Z");
  const now = moment();
  let handler;

  const clock = {
    days: targetDate.diff(now, "days"),
    hours: targetDate.diff(now, "hours") % 24,
    minutes: targetDate.diff(now, "minutes") % 60,
    seconds: targetDate.diff(now, "seconds") % 60,
    targetDate: targetDate.format(),
    freeze: now.isAfter(targetDate)
  };

  function zeros(num) {
    if (num < 10)
      return '0' + num;
    return '' + num;
  }

  function updateView() {
    document.getElementById('th').textContent = zeros(clock.hours);
    document.getElementById('tm').textContent = zeros(clock.minutes);
    document.getElementById('ts').textContent = zeros(clock.seconds);
    document.getElementById('td').textContent = zeros(clock.days);
  }

  if (clock.days > 0)
    document.getElementById('dd').style.display = '';

  updateView();

  if (clock.freeze)
    return;

  handler = setInterval(() => {
    clock.seconds--;

    if (clock.seconds < 0) {
      if (clock.minutes <= 0 && clock.hours <= 0 && clock.days <= 0) {
        clock.freeze = true;
        clearInterval(handler);
        return;
      }

      clock.seconds = 59;
      --clock.minutes;
    }

    if (clock.minutes < 0) {
      clock.minutes = 59;
      --clock.hours;
    }

    if (clock.hours < 0) {
      clock.hours = 23;
      --clock.days;
    }

    updateView();
  }, 1000);
})()
