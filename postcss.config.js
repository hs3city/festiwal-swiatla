module.exports = {
  plugins: [
    ...(process.env.HUGO_ENVIRONMENT === 'production' ? [
        require('cssnano')({
            preset: 'advanced',
        })
    ] : [])
  ]
};
