# Uebung_012k: String Input und Speichern INI mit Subapp

* * * * * * * * * *
## Einleitung
Diese Übung demonstriert das Einlesen eines String-Wertes von einer Eingabequelle (z. B. einem Touch-Eingabefeld) und das dauerhafte Speichern dieses Wertes in einer INI-Datei. Die gesamte Funktionalität ist in einer Subapp gekapselt, die als wiederverwendbarer Baustein zur Verfügung steht. Der gespeicherte Wert steht nach jedem Lese- oder Speichervorgang als Ausgang zur Verfügung und wird gleichzeitig an eine Ausgabekomponente (z. B. Display) übermittelt.

## Verwendete Funktionsbausteine (FBs)
### Sub-Baustein: `Uebung_012k_sub`
- **Typ**: SubAppType
- **Verwendete interne FBs**:
    - **`StringValue_IS`**: `isobus::UT::io::StringValue::StringValue_IS`
        - Parameter: `QI` = `TRUE`
        - Beschreibung: Dieser FB liest den aktuellen String-Wert von einer über `u16ObjId` spezifizierten Eingabequelle. Wird ein neuer Wert erkannt, erzeugt er ein Ereignis am Ausgang `IND`.
    - **`INI`**: `eclipse4diac::storage::INI`
        - Parameter: `QI` = `TRUE`, `DEFAULT_VALUE` = `STRING#''`
        - Beschreibung: Der FB speichert einen String-Wert unter einem bestimmten Schlüssel (`KEY`) und Bereich (`SECTION`) in einer INI-Datei. Er unterstützt die Ereignisse `SET` (Speichern), `GET` (Laden) und `INIT` (Initialisierung).
    - **`Q_StringValue`**: `isobus::UT::Q::Q_StringValue`
        - Parameter: keine (Parameter werden über Datenverbindungen gesetzt)
        - Beschreibung: Dieser FB konvertiert den von `INI` gelieferten Binär-String in ein Ausgabeformat und sendet ihn an die durch `u16ObjId` identifizierte Ausgabestelle (z. B. Display).
- **Funktionsweise**:
    1. **Initialisierung**: Beim Start wird das `INIT`-Ereignis des `INI`-FBs ausgelöst. Dieses triggert intern ein `GET`, sodass der zuletzt gespeicherte Wert aus der INI-Datei geladen wird.
    2. **Speichern eines neuen Wertes**: Wenn der `StringValue_IS`-FB einen neuen Eingabewert erkennt, sendet er ein Ereignis an den `SET`-Eingang von `INI`. Daraufhin speichert `INI` den aktuellen Wert unter dem vorgegebenen `KEY` und `SECTION` ab und gibt das Ereignis `SETO` aus.
    3. **Lesen und Ausgeben**: Sobald `INI` einen `GET`-Vorgang abschliesst (sowohl nach INIT als auch nach jedem SET – hier jedoch nur nach INIT realisiert), wird über `GETO` das Ereignis an den `REQ`-Eingang von `Q_StringValue` und gleichzeitig an den Ausgang `IND` der SubApp weitergeleitet. Der geladene String wird über `VALUEO` direkt nach aussen gegeben und von `Q_StringValue` an die Ausgabestelle gesendet.

## Programmablauf und Verbindungen
Der oberste Baustein `Uebung_012k` besitzt keine eigene Schnittstelle (leere `SubAppInterfaceList`). Er instanziiert den Sub-Baustein `Uebung_012k_sub` und übergibt diesem drei konstante Parameter:
- `KEY` = `KEY_I1_STORE`
- `SECTION` = `SECTION_I1_STORE`
- `u16ObjId` = `InputString_S1`

Diese Konstanten sind in den referenzierten Bibliotheken definiert und legen fest, unter welchem Schlüssel und Bereich der String in der INI-Datei abgelegt wird, sowie welche Eingabe-/Ausgabekomponente verwendet wird.

**Verbindungen im Sub-Baustein**:
- Ereignisfluss:
    - `StringValue_IS.IND` → `INI.SET`
    - `INI.SETO` → `IND` (Ausgang der SubApp)
    - `INI.GETO` → `Q_StringValue.REQ` und `IND`
    - `INI.INITO` → `INI.GET`
- Datenfluss:
    - `StringValue_IS.IN` → `INI.VALUE`
    - `u16ObjId` → `StringValue_IS.u16ObjId` und `Q_StringValue.u16ObjId`
    - `KEY` → `INI.KEY`
    - `SECTION` → `INI.SECTION`
    - `INI.VALUEO` → `Q_StringValue.pau8String` und `VALUEO` (Ausgang der SubApp)

**Beachte**: Nach einem Speichervorgang (`SET`) wird aktuell kein erneutes `GET` ausgelöst. Daher wird der neu gespeicherte Wert erst bei der nächsten Initialisierung oder einem manuellen `GET` gelesen und an die Ausgabe weitergegeben. In der vorliegenden Konfiguration dient dies dem einmaligen Speichern eines Startwertes, der beim Neustart wiederhergestellt wird.

## Zusammenfassung
Die Übung zeigt den Umgang mit String-Eingaben, der persistierenden Speicherung in INI-Dateien sowie der gekapselten Wiederverwendung von Funktionalität durch eine Subapp. Der `INI`-FB übernimmt das Speichern und Laden, während `StringValue_IS` und `Q_StringValue` die Kommunikation mit der Hardware (Eingabe/Ausgabe) realisieren. Die Subapp `Uebung_012k_sub` kann in übergeordneten Projekten einfach per Parameterkonfiguration an unterschiedliche Objekt-IDs und Speicherorte angepasst werden.