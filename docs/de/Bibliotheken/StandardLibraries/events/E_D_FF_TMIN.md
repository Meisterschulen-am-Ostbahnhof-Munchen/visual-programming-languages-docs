# E_D_FF_TMIN

* * * * * * * * * *

## Einleitung

Der `E_D_FF_TMIN` kombiniert `E_D_FF` (taktgesteuertes `BOOL`-Latch mit Änderungserkennung) mit [E_TMIN](E_TMIN.md) (Mindestabstandszeit): Änderungen von `Q` werden weiterhin sofort in `Q` übernommen, das Änderungsereignis `EO` wird jedoch zusätzlich auf höchstens eine Auslösung pro `Tmin`-Intervall begrenzt.

![E_D_FF_TMIN](E_D_FF_TMIN.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **INIT**: Initialisierung, trägt `Tmin`.
- **CLK**: Taktereignis, übernimmt `D` in `Q`.
    - **Verbundene Daten**: `D`

### **Ereignis-Ausgänge**

- **INITO**: Bestätigt die Initialisierung.
- **EO**: Auf `Tmin` gedrosseltes Änderungsereignis.
    - **Verbundene Daten**: `Q`

### **Daten-Eingänge**

- **D** (BOOL): Der zu speichernde Wert.
- **Tmin** (TIME): Mindestabstand zwischen zwei `EO`-Ereignissen.

### **Daten-Ausgänge**

- **Q** (BOOL): Der zuletzt übernommene Wert.

## Funktionsweise

`CLK` triggert intern das gekapselte `E_D_FF`, dessen `D`/`Q`-Datenverbindung direkt auf die äußeren Anschlüsse `D`/`Q` durchgereicht wird. Nur wenn `E_D_FF` eine echte Wertänderung erkennt (`Q := D`), löst es sein eigenes `EO` aus — dieses wird an den `EI`-Eingang des internen [E_TMIN](E_TMIN.md) weitergeleitet, welches das Ereignis nur dann an den äußeren `EO`-Ausgang durchlässt, wenn seit dem letzten Durchlass mindestens `Tmin` vergangen ist.

## Technische Besonderheiten

- **Zweistufige Filterung**: Erst inhaltliche Änderungserkennung (`E_D_FF`), dann zeitliche Drosselung (`E_TMIN`) — `Q` selbst wird davon nicht beeinflusst und ist stets aktuell, auch wenn `EO` gerade gedrosselt wird.
- **Reine Verdrahtung aus zwei Standardbausteinen**, kein eigenes ECC.

## Zustandsübersicht

Zustandslose Verdrahtungslogik, siehe `E_D_FF` (Änderungserkennung) und [E_TMIN](E_TMIN.md) (Zeitdrosselung) für die jeweiligen internen Zustände.

## Anwendungsszenarien

- **Rauscharme Statusmeldung eines `BOOL`-Signals**: Ein digitaler Zustand ändert sich häufig kurzfristig (Prellen, Rauschen); `EO` soll aber höchstens alle `Tmin` ausgelöst werden, während `Q` jederzeit den aktuellen Wert zeigt.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **`E_D_FF`**: dieselbe Änderungserkennung, aber ohne Zeitdrosselung.
- **[E_D_FF_ANY_TMIN](E_D_FF_ANY_TMIN.md)**: dieselbe Funktion für beliebige Datentypen statt nur `BOOL`.
- **[E_TMIN](E_TMIN.md)**: die intern verwendete Drosselungslogik.

## Fazit

`E_D_FF_TMIN` liefert ein änderungserkennendes `BOOL`-Latch mit garantiertem Mindestabstand zwischen den Änderungsereignissen und eignet sich für rauscharme Ereignisweiterleitung digitaler Signale.
