# wolf3d @ 42

![wolf3d screenshot](/screens/screen1.png?raw=true)

![wolf3d screenshot](/screens/screen2.png?raw=true)

A Wolfeinstein-like renderer made in C using minilibX, with textures, basic
lighting and basic map files.

## Compiling
Run `make` and you're set. Runs on Mac OS X and Linux (with XServer).
Make sure to enable set the `HI_RES = 1` macro if you want to use the high
resolution textures included.

## Running
Run `./wolf3d [map_file]`, a window should appear. You can navigate through the
map using the arrow keys. Exit by closing the window or pressing ESC.

## Map file format
It's a very simple format. Open a file in your favorite text editor, make sure
you have a grid of integers (each one being it's block ID), and it should work
right out of the box. You can specify a spawn position with `x`.

```
1 1 1 1 1
1 0 2 0 1
1 0 x 0 1
1 1 1 1 1
```

## License
This project is licensed under the GNU General Public License 3.

Textures are by [@wht_dragon](https://twitter.com/wht_dragon). High resolution
textures belong to their respective owners.
