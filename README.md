# Description

This is a simple console typing speed test. You will be presented with a text, which you will have to type correctly as fast as you can. The timer will start after your first input and when you have finished typing the text, your typing speed will be calculated. The text will be color coded according to your input and there is also an extra blinker on top to notify you if you have typed anything wrong.


# Build & Run

For a better experience use a terminal size of 80x24 and a font size of 12.

You will need a standards-compliant C compiler, the standard C library with header files, and make. On Debian GNU/Linux and derivatives, you can install these with

	$ apt install build-essential

After that clone the repository and cd into it

	$ git clone https://github.com/xemeds/typing-test.git

	$ cd typing-test

Build and run with

	$ make

	$ ./typing

# References

Texts: [typeracer.com](https://typeracer.com/)

# License

This project is under the [MIT](https://github.com/xemeds/typing-test/blob/master/LICENSE) license.
