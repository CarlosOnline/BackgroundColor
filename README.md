# BackgroundColor Utility
Change windows console / command window background color only.  

Other features:
- Change background only.
- Change background and foreground color.
- Change foreground only.
- Change background &/or foreground color for new lines only, leaving existing lines unchanged.

Created by Carlos Gomes <cgomes@iinet.com>

#### Arguments:
```
        background     - specifies background color name. Use none to keep current background color.
        foreground     - (optional) specifies foreground color name. If not specified then not changed.
        process id     - (optional) attach to console application for testing.
                          Defaults to current console.
        -newlines      - changes the colors for new lines only, previous lines are untouched.
```

#### Examples:
```
        BackgroundColor.exe blue
                        Changes background color only to blue on all lines.

        BackgroundColor.exe red white
                        Changes background & foreground color on all lines.

        BackgroundColor.exe blue -newlines
                        Changes background color only to blue on new lines only.  Existing lines are not changed.

        BackgroundColor.exe red white
                        Changes background & foreground color on new lines only.  Existing lines are not changed.

        BackgroundColor.exe none red
                        Changes foreground color only on all lines.
```

#### Color Names:
   Any of the variations below can be used.

```
Black
Gray
DarkBlue
Blue      LightBlue    Light Blue     BrightBlue      Bright Blue
Green     LightGreen   Light Green    BrightGreen     Bright Green
Aqua      LightAqua    Light Aqua     BrightAqua      Bright Aqua
Red       LightRed     Light Red      BrightRed       Bright Red
Purple    LightPurple  Light Purple   BrightPurple    Bright Purple
Yellow    LightYellow  Light Yellow   BrightYellow    Bright Yellow
White     LightWhite   Light White    BrightWhite     Bright White
```
