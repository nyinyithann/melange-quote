const path = require('path');
const Dotenv = require('dotenv-webpack');

module.exports = {
    mode: 'development',
    plugins: [
        new Dotenv({
            path: path.resolve(__dirname, '..', './.env.development'),
        }),
    ],
    devServer: {
        historyApiFallback: true,
        hot: true,
        open: true,
        host: '0.0.0.0',
        port: 8080,
        proxy: {
            '/dev': {
                target: {
                    host: 'localhost',
                    protocol: 'http:',
                    port: 3000,
                },
                pathRewrite: {
                    '^/dev': '',
                },
            },
        },
    },
    devtool: 'source-map',
};
