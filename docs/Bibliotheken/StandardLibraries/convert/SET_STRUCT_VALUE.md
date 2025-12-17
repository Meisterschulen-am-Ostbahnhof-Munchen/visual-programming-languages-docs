# SET_STRUCT_VALUE

<img width="1393" height="152" alt="image" src="https://github.com/user-attachments/assets/06ce9694-a203-4982-895d-68c27425acd1" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `SET_STRUCT_VALUE` ist ein Service-Schnittstellen-Funktionsblock, der dazu dient, einen bestimmten Wert innerhalb einer Datenstruktur zu setzen. Er ermöglicht die dynamische Manipulation von Strukturelementen, indem er einen neuen Wert für ein benanntes Mitglied der Struktur zuweist.

## Schnittstellenstruktur
Der Funktionsblock verfügt über Ereignis- und Datenschnittstellen, um seine Funktionalität zu ermöglichen.

### **Ereignis-Eingänge**
*   **REQ**: Dieses Ereignis fordert den Funktionsblock auf, den Wert in der angegebenen Struktur zu setzen. Es ist mit den Datenvariablen `member`, `in_struct` und `element_value` assoziiert.

### **Ereignis-Ausgänge**
*   **CNF**: Dieses Ereignis wird ausgelöst, wenn die `REQ`-Anforderung abgeschlossen wurde. Es ist mit der Datenvariable `out_struct` assoziiert.

### **Daten-Eingänge**
*   **in_struct** (Typ: ANY): Die Eingabestruktur, in der ein Wert geändert werden soll. Der Typ `ANY` ermöglicht die Verarbeitung beliebiger Strukturtypen.
*   **member** (Typ: STRING): Der Name des Strukturmitglieds, dessen Wert gesetzt werden soll. Innere Mitglieder können über den Punktoperator (`.`) angesprochen werden (z.B. "config.port").
*   **element_value** (Typ: ANY): Der neue Wert, der dem angegebenen Strukturmitglied zugewiesen werden soll.

### **Daten-Ausgänge**
*   **out_struct** (Typ: ANY): Die modifizierte Struktur nach dem Setzen des Elements. Der Kommentar im XML besagt "TRUE if no errors ocurred, FALSE otherwise", was ein Überbleibsel eines `STATUS`-Ausgangs ist, aber hier bezieht es sich auf die ausgegebene, geänderte Struktur.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Nach Empfang eines `REQ`-Ereignisses greift der Funktionsblock auf die über `in_struct` bereitgestellte Datenstruktur zu. Basierend auf dem als `member` übergebenen String wird das entsprechende Element innerhalb der Struktur identifiziert. Der Funktionsblock weist dann den über `element_value` bereitgestellten Wert diesem Element zu. Anschließend gibt der Funktionsblock die modifizierte Struktur über `out_struct` aus und signalisiert den Abschluss des Vorgangs durch das `CNF`-Ereignis.

## Technische Besonderheiten
*   **Generische Typen (ANY)**: Durch die Verwendung des Datentyps `ANY` für `in_struct`, `element_value` und `out_struct` bietet dieser Funktionsblock hohe Flexibilität. Er kann mit beliebigen benutzerdefinierten oder vordefinierten Strukturtypen und Werten arbeiten, ohne dass spezifische Typen zur Kompilierzeit bekannt sein müssen.
*   **Zugriff auf verschachtelte Mitglieder**: Die `member`-Variable unterstützt den Zugriff auf tiefere Ebenen einer verschachtelten Struktur mithilfe der Punktnotation (z.B. "outer.inner.value"). Dies vereinfacht die Handhabung komplexer Datenmodelle.

## Zustandsübersicht
Der Funktionsblock operiert hauptsächlich in einem anforderungsbasierten (`REQ`) und bestätigungsbasierten (`CNF`) Schema. Er verarbeitet eine Anforderung, ändert die Daten und signalisiert den Abschluss. Es gibt keine komplexen internen Zustände, die über diesen einfachen Request/Confirm-Zyklus hinausgehen.

## Anwendungsszenarien
*   **Konfigurationsmanagement zur Laufzeit**: Dynamisches Ändern von Konfigurationsparametern, die in Strukturen gespeichert sind, ohne den Funktionsblock neu kompilieren zu müssen.
*   **Datenmanipulation in SCADA/HMI-Systemen**: Aktualisieren spezifischer Werte in komplexen Datenobjekten, die von übergeordneten Systemen empfangen oder an diese gesendet werden.
*   **Schnittstellen zu externen Systemen**: Anpassen von Datenstrukturen, die für die Kommunikation mit externen APIs oder Datenbanken verwendet werden.
*   **Prozesssteuerung**: Modifizieren von Prozessparametern, die in Strukturen organisiert sind, basierend auf dynamischen Bedingungen oder Benutzereingaben.

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu Bausteinen, die fest verdrahtete Strukturen oder nur das Auslesen von Werten unterstützen, bietet `SET_STRUCT_VALUE` eine einzigartige Flexibilität durch:
*   **Schreibzugriff**: Ermöglicht das Setzen von Werten, nicht nur das Lesen.
*   **Generischer Zugriff**: Arbeitet mit beliebigen `ANY`-Typen, was ihn universeller macht als Bausteine, die an spezifische Strukturtypen gebunden sind.
*   **Dynamische Member-Auswahl**: Der Member-Name wird zur Laufzeit als String übergeben, was eine dynamischere Feldselektion als bei fest definierten Ein-/Ausgängen erlaubt.
Er ergänzt oft Bausteine, die Werte aus Strukturen auslesen (`GET_STRUCT_VALUE`), um eine vollständige Lese-/Schreibfunktionalität für generische Strukturen zu bieten.

## Fazit
Der `SET_STRUCT_VALUE`-Funktionsblock ist ein mächtiges Werkzeug für die dynamische Manipulation von Datenstrukturen innerhalb einer 4diac-Anwendung. Seine generische Natur und die Unterstützung für den Zugriff auf verschachtelte Mitglieder machen ihn äußerst vielseitig für Anwendungen, die eine flexible Konfiguration oder Datenverarbeitung zur Laufzeit erfordern.
