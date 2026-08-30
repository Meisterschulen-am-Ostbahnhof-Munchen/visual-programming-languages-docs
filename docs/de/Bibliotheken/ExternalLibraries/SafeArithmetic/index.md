# SafeArithmetic

Saturierende (klemmende) Arithmetik-Funktionsbausteine, entwickelt unter EPL-2.0-Lizenz von
HR Agrartechnik GmbH. Motiviert durch einen echten Hardware-Befund (`Uebung_011b3`): normale
IEC-61131-3-Arithmetik läuft bei Integer-Typen bei Über-/Unterlauf still über und erzeugt bei
REAL/LREAL `INF`/`NaN` — beides gefährlich für reale Messwerte. Jeder Baustein dieser Bibliothek
klemmt das Ergebnis stattdessen auf den gültigen Bereich und meldet die Grenzwertverletzung über
einen `LIMIT_HIT`-Ausgang.

```{toctree}
:maxdepth: 1

arithmetic/index
```
