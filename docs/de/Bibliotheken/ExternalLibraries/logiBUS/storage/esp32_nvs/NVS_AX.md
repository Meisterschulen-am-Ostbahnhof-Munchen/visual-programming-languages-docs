# NVS_AX

![NVS_AX](NVS_AX.svg)

* * * * * * * * * *

## Einleitung

`NVS_AX` lädt und speichert einen `BOOL`-Wert unter einem Schlüssel (`KEY`) im nichtflüchtigen Speicher (Non-Volatile Storage, NVS) des ESP32. Er ist das boolesche Gegenstück zu [NVS_AB](NVS_AB.md) und verwendet dieselbe Zwei-Adapter-Architektur, jedoch mit unidirektionalen `AX`-Adaptern statt `AB`.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **INIT**: Initialisiert den Baustein und liest den unter `KEY` hinterlegten Wert (bzw. `DEFAULT_VALUE`, falls noch keiner existiert). Liefert `QI`, `SETM`, `KEY`, `DEFAULT_VALUE`.

### **Ereignis-Ausgänge**

- **INITO**: Bestätigt Initialisierung und den ersten Lesezugriff, liefert `QO` und `STATUS`.

### **Daten-Eingänge**

- **QI** (BOOL): Qualifizierer des `INIT`-Ereignisses.
- **SETM** (BOOL): Gibt das Spiegeln (Rückmeldung) beim Schreiben (`SET`) frei.
- **KEY** (STRING): Name des Schlüssels im NVS.
- **DEFAULT_VALUE** (BOOL): Wert, der geliefert wird, wenn unter `KEY` noch nichts im NVS gespeichert ist.

### **Daten-Ausgänge**

- **QO** (BOOL): Erfolgsqualifizierer, mit `INITO` sowie den internen Adapterbestätigungen mitgeliefert.
- **STATUS** (STRING): Statusmeldung des NVS-Zugriffs.

### **Adapter**

- **AX_IN** (Socket, Typ `AX`): Neuer zu speichernder Wert -- ein Adapterereignis auf `AX_IN.E1` löst einen `SET` im internen NVS-Baustein aus, `AX_IN.D1` liefert den zu schreibenden Wert.
- **AX_OUT** (Plug, Typ `AX`): Gibt den zuletzt gelesenen Wert aus -- sowohl nach dem automatischen Erstlesen bei `INIT` als auch nach jedem bestätigten Schreibvorgang (`AX_OUT.D1`/`AX_OUT.E1`).

## Funktionsweise

`NVS_AX` kapselt intern eine Instanz von `logiBUS::storage::esp32_nvs::NVS` sowie ein `E_PERMIT`-Gatter (`SET_PERMIT`). Bei `INIT` wird die interne NVS-Instanz initialisiert (`NVS.INIT`) und anschließend automatisch ein `GET` ausgelöst, das den unter `KEY` gespeicherten Wert (oder `DEFAULT_VALUE`) liefert; das Ergebnis wird über `AX_OUT` ausgegeben, `INITO` bestätigt den Abschluss.

Zum Schreiben liefert der an `AX_IN` angeschlossene Baustein ein Adapterereignis (`AX_IN.E1`) mit dem neuen Wert (`AX_IN.D1`); dies löst `NVS.SET` aus. Ob die erfolgreiche Speicherung zusätzlich über `AX_OUT` zurückgemeldet wird, steuert `SETM`: Ist `SETM` gesetzt, gibt `SET_PERMIT` das `AX_OUT.E1`-Ereignis nach erfolgreichem `SET` frei ("Mirroring").

## Technische Besonderheiten

- Reines Composite-FB ohne eigene ECC -- die eigentliche Flash-Logik steckt in der internen `NVS`-Instanz, `NVS_AX` verdrahtet nur Ereignisse und Daten zwischen ihr und den beiden `AX`-Adaptern.
- Zwei getrennte, unidirektionale Adapter (`AX_IN`/`AX_OUT`) -- dadurch lassen sich Lese- und Schreibpfad an unterschiedliche Gegenstellen anschließen.
- `SETM` steuert nur, ob ein Schreibvorgang zusätzlich per Adapterereignis über `AX_OUT` gespiegelt wird -- gespeichert wird in jedem Fall.

## Zustandsübersicht

Der Baustein ist zustandslos im Sinne einer eigenen ECC: Er durchläuft bei `INIT` einmalig Initialisierung + Erstlesen, danach reagiert er auf jedes `AX_IN`-Adapterereignis mit einem NVS-Schreibzugriff und optional einer Bestätigung über `AX_OUT`.

## Anwendungsszenarien

- Persistieren einzelner `BOOL`-Konfigurationswerte (z. B. Freigabe-Flags, Betriebsartenschalter) auf dem ESP32
- Aufbau eines Lese-/Schreibpaars, bei dem Lese- und Schreibseite an unterschiedliche Bausteine angeschlossen werden sollen
- Wiederherstellen eines zuletzt gespeicherten `BOOL`-Werts nach einem Neustart über `AX_OUT`

## ⚖️ Vergleich mit ähnlichen Bausteinen

Vergleich mit [NVS_AB](NVS_AB.md), das dieselbe Architektur für `BYTE`- statt `BOOL`-Werte nutzt, sowie mit [INI_AX](../ini/INI_AX.md), das dieselbe Schnittstelle für die textbasierte `settings.ini` statt für den NVS-Flash-Speicher bereitstellt.

## Fazit

`NVS_AX` bietet einen einfachen, unidirektional verdrahteten Zugriff auf einen persistenten `BOOL`-Wert im ESP32-NVS und eignet sich überall dort, wo Lese- und Schreibpfad getrennt geführt werden sollen.
