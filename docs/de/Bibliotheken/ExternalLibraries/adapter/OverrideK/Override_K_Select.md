# Override_K_Select

![Override_K_Select](Override_K_Select.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `Override_K_Select` wandelt ein Paar boolescher Override-Signale
(`Aktiv`/`Wert`, je als [AX](../types/unidirectional/BOOL/AX.md)-Adapter) in einen einzelnen
`UINT`-Selektor `K` (als [AUI](../types/unidirectional/UINT/AUI.md)-Adapter) um, wie ihn ein
`AX_AUI_MUX_3` erwartet. Er kapselt damit das im Projekt wiederkehrende Muster "ein Sensorwert
kann per RW-Override entweder auf `FALSE` oder `TRUE` erzwungen werden" (siehe
`Sensor.Leermelder.Override.*` in `docs/datenpunkte.md` der Getreideannahme-Anwendung) in einem
einzigen, wiederverwendbaren Baustein, statt die Umrechnung an jeder Verwendungsstelle erneut zu
verdrahten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine eigenen Ereignis-Eingänge. Ereignisse laufen ausschließlich über die Adapter-Sockets
`Aktiv`/`Wert`.

### **Ereignis-Ausgänge**

Keine eigenen Ereignis-Ausgänge. Das Ergebnis wird über den Adapter-Plug `K` ausgegeben.

### **Daten-Eingänge**

Keine eigenen Daten-Eingänge. Alle Daten werden über die Adapter-Sockets übertragen.

### **Daten-Ausgänge**

Keine eigenen Daten-Ausgänge. Das Ergebnis wird über den Adapter-Plug `K` ausgegeben.

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
| ---------- | ------ | ----- | -------------- |
| Socket (Eingang) | `Aktiv` | `adapter::types::unidirectional::AX` | `Override.Aktiv` |
| Socket (Eingang) | `Wert` | `adapter::types::unidirectional::AX` | `Override.Wert` |
| Plug (Ausgang) | `K` | `adapter::types::unidirectional::AUI` | 0=Normal (`Aktiv`=FALSE), 1=Force FALSE (`Aktiv`=TRUE, `Wert`=FALSE), 2=Force TRUE (`Aktiv`=TRUE, `Wert`=TRUE) |

## Funktionsweise

Intern arbeitet der Baustein mit zwei verketteten, generischen `F_SEL`-Bausteinen (Standard-
IEC-61131-3-Selektor `OUT := G ? IN1 : IN0`) statt mit eigener ST-Logik:

1. **`F_SEL_Wert`**: `G := Wert.D1`. Liefert `Override_K_ForceFalse` (1) wenn `Wert = FALSE`,
   sonst `Override_K_ForceTrue` (2). Ausgelöst durch `Wert.E1`.
2. **`F_MOVE`** (Attribut `DataType="UINT"`): Übernimmt `F_SEL_Wert.OUT`, ausgelöst durch
   `F_SEL_Wert.CNF`. Dient als Typ-Anker für das generische `ANY`-Ergebnis von `F_SEL` (siehe
   Technische Besonderheiten) und stößt anschließend `F_SEL_Aktiv` erneut an.
3. **`F_SEL_Aktiv`**: `G := Aktiv.D1`. Liefert `Override_K_Normal` (0) wenn `Aktiv = FALSE`, sonst
   den zuletzt von `F_MOVE` gehaltenen Wert (1 oder 2). Ausgelöst sowohl direkt durch `Aktiv.E1`
   als auch indirekt über `F_MOVE.CNF`, sodass eine Änderung von `Wert` auch bei unverändertem
   `Aktiv` sofort ein neues `K` erzeugt.
4. `F_SEL_Aktiv.OUT`/`F_SEL_Aktiv.CNF` werden direkt auf die Datenausgangsvariable `K.D1` bzw. das
   Ereignis `K.E1` des eigenen Plugs geschrieben — ohne eine zusätzliche `_TO_AUI`-Konvertierungs-
   FB dazwischenzuschalten (siehe Technische Besonderheiten).

## Technische Besonderheiten

- **Direktes Schreiben auf die eigenen Plug-Pins.** Statt eine `UINT_TO_AUI`-artige
  Konvertierungs-FB zwischenzuschalten, verbindet der Baustein `F_SEL_Aktiv.OUT`/`.CNF` direkt mit
  `K.D1`/`K.E1` — den vom `AUI`-Adaptertyp selbst deklarierten Event-/Datenvariablen des eigenen
  Plugs. Dasselbe Prinzip nutzen auch
  [const_AX_TRUE](../types/unidirectional/BOOL/constants/const_AX_TRUE.md) und
  [const_AX_FALSE](../types/unidirectional/BOOL/constants/const_AX_FALSE.md) für ihren `OUT`-Plug.
- **`F_MOVE` als Typ-Anker für `F_SEL`s generisches `ANY`-Ergebnis.** `F_SEL.OUT` ist generisch
  (`ANY`); ohne einen nachgeschalteten `F_MOVE` mit festem `DataType`-Attribut lässt sich der Wert
  nicht sauber als `UINT` an den zweiten `F_SEL`-Aufruf weiterreichen.
- **Die K-Werte sind benannte Konstanten, keine Literale.** `Override_K_Normal`/
  `Override_K_ForceFalse`/`Override_K_ForceTrue` kommen aus dem globalen Konstantenpaket
  [Override_K](const/Override_K.md) (`adapter::OverrideK::const`), nicht als `UINT#0`/`UINT#1`/
  `UINT#2`-Literale direkt in den `F_SEL`-Parametern.
- **Kein eigenes `REQ`/`CNF`.** Der Baustein reagiert ausschließlich auf die Ereignisse der
  Sockets selbst (`Aktiv.E1`, `Wert.E1`) — es gibt keinen externen Trigger-Eingang.

## Zustandsübersicht

Der Baustein besitzt keine eigene Zustandsmaschine (Composite-FB ohne ECC); sein Verhalten ist
rein kombinatorisch, neu berechnet bei jeder Änderung von `Aktiv` oder `Wert`.

| Aktiv | Wert | K |
| :---: | :---: | :---: |
| FALSE | — | 0 (Normal) |
| TRUE | FALSE | 1 (Force FALSE) |
| TRUE | TRUE | 2 (Force TRUE) |

## Anwendungsszenarien

- **Sensor-Override mit RW-OPC-UA-Knoten**: Ein per `AX_SUBSCRIBE_1` abonnenntes `Aktiv`/`Wert`-
  Paar (z. B. `Sensor.Leermelder.Override.Aktiv`/`.Wert`) direkt in den `K`-Eingang eines
  `AX_AUI_MUX_3` speisen, dessen drei Eingänge Normalwert, `FALSE` und `TRUE` bereitstellen.
- **Diagnose-/Testseiten**: Jeder boolesche Sensor, der über eine Weboberfläche testweise auf
  einen festen Wert erzwungen werden soll, kann dasselbe `Aktiv`/`Wert`/`K`-Muster wiederverwenden.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **[AX_AUI_MUX_3](../selection/unidirectional/BOOL/AX_AUI_MUX_3.md)**: der eigentliche
  Multiplexer, den `Override_K_Select` mit seinem `K`-Ausgang ansteuert. `Override_K_Select`
  berechnet nur den Selektor, wählt aber selbst keinen Wert aus.
- **[const_AX_TRUE](../types/unidirectional/BOOL/constants/const_AX_TRUE.md) /
  [const_AX_FALSE](../types/unidirectional/BOOL/constants/const_AX_FALSE.md)**: liefern die
  festen `IN2`/`IN3`-Werte (Force FALSE/TRUE), die der von `Override_K_Select` berechnete
  Selektor am `AX_AUI_MUX_3` auswählt.
- **[Override_K](const/Override_K.md)**: das globale Konstantenpaket mit den drei benannten
  K-Werten, die dieser Baustein intern verwendet.

## Fazit

`Override_K_Select` bündelt die Umrechnung eines Aktiv/Wert-Override-Paars in einen MUX-Selektor
in einem einzigen, wiederverwendbaren Baustein, gebaut ausschließlich aus Standard-Bausteinen
(`F_SEL`, `F_MOVE`) ohne eigene ST-Algorithmen. Kombiniert mit `AX_AUI_MUX_3` und den
`const_AX_TRUE`/`const_AX_FALSE`-Konstanten ergibt sich damit das komplette, wiederverwendbare
Muster für einen per OPC-UA erzwingbaren booleschen Sensorwert.
