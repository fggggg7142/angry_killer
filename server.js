const express = require('express');
const request = require('request');

const app = express();

app.all('*', (req, res) => {
  const url = 'https://poe.com' + req.originalUrl;
  console.log("= = kaka", url)
  req.pipe(request(url)).pipe(res);
});

app.listen(3000, () => {
  console.log('代理服务器已启动，监听端口 3000');
});
