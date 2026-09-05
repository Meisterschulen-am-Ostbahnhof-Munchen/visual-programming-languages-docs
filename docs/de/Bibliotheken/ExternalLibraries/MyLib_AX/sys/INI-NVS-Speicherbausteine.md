# INI_IN_AND_STORE / NVS_IN_AND_STORE: Gemeinsames Muster

* * * * * * * * * *

## Einleitung

`MyLib::sys` enthält eine Familie von Bausteinen, die einen über VT eingegebenen Wert **persistent speichern** und beim Deployment automatisch wieder laden — entweder in einer INI-Datei (`INI_IN_AND_STORE_*`) oder im ESP32-Flash (NVS, `NVS_IN_AND_STORE_*`). Diese Seite erklärt das gemeinsame Muster.

## Namensschema

`{INI|NVS}_IN_AND_STORE_<Typ>`, wobei `<Typ>` den Datentyp bestimmt: `AIS` (String-Adapter), `AR` (REAL-Adapter, mit physikalischer Skalierung `NumericObjectPool_S`), `AUDI` (UDINT-Adapter) in test_AX; `UDINT` (klassisch, ohne Adapter) in test_B.

## Funktionsweise (test_AX, adapterbasiert)

1. Ein VT-Eingabefeld (`StringValue_AIS`/`NumericValue_PHYSA`/…) liefert den vom Nutzer eingegebenen Wert als Adapter.
2. `INI_<Typ>`/`NVS_<Typ>` (`eclipse4diac::storage::INI_*` bzw. `logiBUS::storage::esp32_nvs::NVS_*`) speichert diesen Wert persistent unter `KEY`/`SECTION` (nur INI) und gibt beim `INIT` den zuletzt gespeicherten Wert zurück (`SETM=TRUE`: Speichern aktiv, `DEFAULT_VALUE`: Anfangswert, falls noch nichts gespeichert).
3. Der (neu geladene oder neu eingegebene) Wert wird über `<Typ>_SPLIT_2` verzweigt: einmal als Plug `VALUEO` nach außen (Weiterverwendung im aufrufenden Netzwerk) und einmal an `Q_StringValue_AIS`/`Q_NumericValue_PHYSA` (Rückschreiben auf das VT-Anzeigefeld, damit Eingabefeld und Anzeige synchron bleiben).

## Funktionsweise (test_B, klassisch)

Die `test_B`-Variante (`INI_IN_AND_STORE_UDINT`/`NVS_IN_AND_STORE_UDINT`) ist älter und nutzt klassische Ereignis-/Datenverbindungen statt Adapter: Ein `NumericValue_ID`-Eingabefeld liefert einen DWORD-Wert, der über `F_DWORD_TO_UDINT` in UDINT gewandelt und an `INI`/`NVS` (generische, nicht typspezifische Bausteine) übergeben wird. Der gespeicherte Wert geht sowohl als `VALUEO` nach außen als auch zurück an `Q_NumericValue` für die Anzeige.

## Zusammenfassung

Beide Varianten lösen dasselbe Problem — "vom Nutzer eingegebenen Wert über Neustarts hinweg merken" — mit demselben Grundmuster (Eingabefeld → Speicher-FB mit KEY/SECTION → Verzweigung auf Ausgang + Anzeige-Rückschreibung), nur mit unterschiedlichem Speicherort (INI-Datei vs. NVS-Flash) und unterschiedlichem Verdrahtungsstil (Adapter in test_AX, klassisch in test_B).

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
