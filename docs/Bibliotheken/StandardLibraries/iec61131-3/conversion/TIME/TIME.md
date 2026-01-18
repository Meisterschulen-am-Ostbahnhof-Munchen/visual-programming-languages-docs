# TIME Konvertierungen

```{index} single: TIME Konvertierungen
```

Hier finden Sie Funktionen zur Konvertierung des Datentyps TIME.

**Hinweis zur Erstellung von TIME-Werten (Numerisch zu TIME):**
Wenn Sie einen numerischen Wert (z.B. INT, DINT) in einen TIME-Wert konvertieren möchten (z.B. "Ich habe 500 und will 500ms"), verwenden Sie bitte den Baustein **`F_MULTIME`** aus der Kategorie `arithmetic`.
*   Beispiel: Multiplizieren Sie Ihren Wert mit der Basiseinheit (z.B. `Eingangswert * T#1ms`).
