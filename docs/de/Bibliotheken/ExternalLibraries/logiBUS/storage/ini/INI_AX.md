# INI_AX

![INI_AX](INI_AX.svg)

* * * * * * * * * *

## Einleitung

`INI_AX` lädt und speichert einen `BOOL`-Wert in der `settings.ini`-Datei, adressiert über Abschnitt (`SECTION`) und Schlüssel (`KEY`). Er ist das boolesche Gegenstück zu [INI_AB](INI_AB.md) und das `settings.ini`-Gegenstück zu [NVS_AX](../esp32_nvs/NVS_AX.md).

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **INIT**: Initialisiert den Baustein und liest den unter `SECTION`/`KEY` hinterlegten Wert (bzw. `DEFAULT_VALUE`, falls noch keiner existiert). Liefert `QI`, `SETM`, `SECTION`, `KEY`, `DEFAULT_VALUE`.

### **Ereignis-Ausgänge**

- **INITO**: Bestätigt Initialisierung und den ersten Lesezugriff, liefert `QO` und `STATUS`.

### **Daten-Eingänge**

- **QI** (BOOL): Qualifizierer des `INIT`-Ereignisses.
- **SETM** (BOOL): Gibt das Spiegeln (Rückmeldung) beim Schreiben (`SET`) frei.
- **SECTION** (STRING): Name des Abschnitts in der `settings.ini`.
- **KEY** (STRING): Name des Schlüssels innerhalb des Abschnitts.
- **DEFAULT_VALUE** (BOOL): Wert, der geliefert wird, wenn unter `SECTION`/`KEY` noch nichts in der `settings.ini` gespeichert ist.

### **Daten-Ausgänge**

- **QO** (BOOL): Erfolgsqualifizierer, mit `INITO` sowie den internen Adapterbestätigungen mitgeliefert.
- **STATUS** (STRING): Statusmeldung des Dateizugriffs.

### **Adapter**

- **AX_IN** (Socket, Typ `AX`): Neuer zu speichernder Wert -- ein Adapterereignis auf `AX_IN.E1` löst einen `SET` im internen INI-Baustein aus, `AX_IN.D1` liefert den zu schreibenden Wert.
- **AX_OUT** (Plug, Typ `AX`): Gibt den zuletzt gelesenen Wert aus -- sowohl nach dem automatischen Erstlesen bei `INIT` als auch nach jedem bestätigten Schreibvorgang (`AX_OUT.D1`/`AX_OUT.E1`).

## Funktionsweise

`INI_AX` kapselt intern eine Instanz von `eclipse4diac::storage::INI` sowie ein `E_PERMIT`-Gatter (`SET_PERMIT`). Bei `INIT` wird die interne INI-Instanz initialisiert (`INI.INIT`) und anschließend automatisch ein `GET` ausgelöst, das den unter `SECTION`/`KEY` gespeicherten Wert (oder `DEFAULT_VALUE`) liefert; das Ergebnis wird über `AX_OUT` ausgegeben, `INITO` bestätigt den Abschluss.

Zum Schreiben liefert der an `AX_IN` angeschlossene Baustein ein Adapterereignis (`AX_IN.E1`) mit dem neuen Wert (`AX_IN.D1`); dies löst `INI.SET` aus. Ob die erfolgreiche Speicherung zusätzlich über `AX_OUT` zurückgemeldet wird, steuert `SETM`: Ist `SETM` gesetzt, gibt `SET_PERMIT` das `AX_OUT.E1`-Ereignis nach erfolgreichem `SET` frei ("Mirroring").

## Technische Besonderheiten

- Reines Composite-FB ohne eigene ECC -- die eigentliche Dateizugriffslogik steckt in der internen `INI`-Instanz, `INI_AX` verdrahtet nur Ereignisse und Daten zwischen ihr und den beiden `AX`-Adaptern.
- Zwei getrennte, unidirektionale Adapter (`AX_IN`/`AX_OUT`) -- dadurch lassen sich Lese- und Schreibpfad an unterschiedliche Gegenstellen anschließen.
- Adressierung über `SECTION` **und** `KEY` (statt nur `KEY` bei den `NVS_*`-Bausteinen) entspricht dem klassischen INI-Dateiformat.

## Zustandsübersicht

Der Baustein ist zustandslos im Sinne einer eigenen ECC: Er durchläuft bei `INIT` einmalig Initialisierung + Erstlesen, danach reagiert er auf jedes `AX_IN`-Adapterereignis mit einem INI-Schreibzugriff und optional einer Bestätigung über `AX_OUT`.

## Anwendungsszenarien

- Persistieren einzelner `BOOL`-Konfigurationswerte (z. B. Freigabe-Flags, Betriebsartenschalter) in einer menschenlesbaren `settings.ini`
- Aufbau eines Lese-/Schreibpaars, bei dem Lese- und Schreibseite an unterschiedliche Bausteine angeschlossen werden sollen
- Konfigurationsdateien, die auch außerhalb der Steuerung (z. B. per Texteditor) einsehbar/änderbar sein sollen

## ⚖️ Vergleich mit ähnlichen Bausteinen

Vergleich mit [INI_AB](INI_AB.md), das dieselbe Architektur für `BYTE`- statt `BOOL`-Werte nutzt, sowie mit [NVS_AX](../esp32_nvs/NVS_AX.md), das dieselbe Schnittstelle für den ESP32-NVS-Flash-Speicher statt für die `settings.ini` bereitstellt.

## Fazit

`INI_AX` bietet einen einfachen, unidirektional verdrahteten Zugriff auf einen persistenten `BOOL`-Wert in der `settings.ini` und eignet sich überall dort, wo Lese- und Schreibpfad getrennt geführt werden sollen.
