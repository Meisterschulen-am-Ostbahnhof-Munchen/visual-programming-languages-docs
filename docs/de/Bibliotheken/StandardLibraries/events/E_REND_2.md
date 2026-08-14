# E_REND_2

* * * * * * * * * *
## Einleitung

Der `E_REND_2` ist die generische 2-Eingangs-Variante des Rendezvous-Bausteins `E_REND` (2 Eingänge). Er löst `EO` erst aus, wenn er von **allen** 2 Eingängen (`EI1`, `EI2`) mindestens ein Ereignis seit dem letzten Reset empfangen hat — eine logische UND-Verknüpfung über 2 asynchrone Ereignisströme.

![E_REND_2](E_REND_2.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **EI1**: Ereigniseingang 1.
- **EI2**: Ereigniseingang 2.
- **R (Reset)**: Setzt den Baustein in seinen Anfangszustand zurück, verwirft alle bisher gemerkten Ereignisse.

### **Ereignis-Ausgänge**

- **EO**: Wird ausgelöst, sobald alle 2 Eingänge seit dem letzten Reset mindestens einmal ausgelöst wurden.

## Funktionsweise

`E_REND_2` ist als generischer Funktionsbaustein implementiert (`eclipse4diac::core::GenericClassName = 'GEN_E_REND'`) — dieselbe C++-Implementierung liegt allen `E_REND_n`-Varianten zugrunde, nur die Anzahl der Eingänge unterscheidet sich. Intern merkt sich der Baustein, welche der `EI1`…`EI2`-Eingänge bereits mindestens ein Ereignis erhalten haben. Sobald alle 2 Eingänge markiert sind, wird `EO` ausgelöst und der interne Merker zurückgesetzt. Ein `R`-Ereignis setzt den Merker jederzeit zurück, ohne `EO` auszulösen.

## Technische Besonderheiten

- **Generische Implementierung**: Wie `E_REND` (2 Eingänge) selbst basiert `E_REND_2` auf derselben generischen `GEN_E_REND`-C++-Klasse; die Eingangsanzahl wird zur Übersetzungszeit über die Typdefinition festgelegt.
- **Reihenfolgeunabhängig**: Die Eingänge `EI1`, `EI2` müssen nicht in einer bestimmten Reihenfolge eintreffen.
- **Automatischer Reset nach Auslösung**: Nach jedem `EO` beginnt der Baustein wieder von vorn.

## Zustandsübersicht

Der Baustein merkt sich intern eine Bitmaske der bereits eingetroffenen Eingänge; bei vollständiger Maske wird `EO` ausgelöst und die Maske geleert.

## Anwendungsszenarien

- **Synchronisation von 2 unabhängigen Vorbedingungen**, bevor ein Folgeschritt ausgelöst wird (z. B. 2 Sensoren müssen alle ausgelöst haben, bevor eine Anlage weiterläuft).
- **Erweiterung von `E_REND`** auf mehr als zwei Ereignisquellen, ohne mehrere `E_REND`-Bausteine kaskadieren zu müssen.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **`E_REND`**: die 2-Eingangs-Basisvariante.
- `E_REND_3`, `E_REND_4`: dieselbe generische Implementierung mit einer anderen Eingangsanzahl.
- **`E_MERGE_2`**: die logische ODER-Verknüpfung mehrerer Ereigniseingänge (feuert bei jedem einzelnen Ereignis statt erst nach allen).

## Fazit

`E_REND_2` erweitert das Rendezvous-Prinzip von `E_REND` auf 2 gleichzeitig zu synchronisierende Ereignisströme und ist die generische, für 2 Eingänge instanziierte Variante derselben zugrunde liegenden Implementierung.
