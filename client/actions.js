$(() => {
  $.get('/device/clock', (data) => {
    $('textarea').val(JSON.stringify(data, 2))
  })
})
