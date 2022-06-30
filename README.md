# DrawByCodeToHtml

## Quick Start
- Build a compiler
```bash
./build.sh
```
- Run an example
```bash
./compiler example.draw index.html
```

## Available commands
- COLOR[`name`, `value`] - create a color, where `value` is a hex color without #, e.g. fc1c03 for red
- rect[`x`, `y`, `height`, `width`] - where `x`, `y`, `height`, `width` in pixels;
- rect[`x`, `y`, `height`, `width`, `color`] - where `color` is a name of created color with `COLOR` command
- rect[`x`, `y`, `height`, `width`, `color`, `angle`] - where `angle` in degrees;
- circle[`x`, `y`, `radius`]
- circle[`x`, `y`, `radius`, `color`]
