import QtQuick 2.12
import QtQuick.Controls 2.12 as QQC2
import QtQuick.Controls.Material 2.3
import Fluid.Controls 1.0 as FluidControls
import "../rrui" as RRUi
import com.gecko.rr.models 1.0 as RRModels
import "../singletons"

ListView {
    id: purchaseTransactionListView

    property Component buttonRow: null
    property string filterText: ""
    property int filterColumn: -1
    property int keys: RRModels.PurchaseTransactionModel.Completed
    property date from: new Date()
    property date to: new Date()

    signal success(int successCode)
    signal error(int errorCode)

    function refresh() { purchaseTransactionListView.model.refresh(); }
    function undoLastCommit() { purchaseTransactionListView.model.undoLastCommit(); }
    function removeTransaction(transactionId) { purchaseTransactionListView.model.removeTransaction(transactionId); }

    bottomMargin: 20
    clip: true
    visible: !model.busy
    headerPositioning: ListView.OverlayHeader

    FluidControls.Placeholder {
        visible: purchaseTransactionListView.count == 0 && !purchaseTransactionListView.model.busy
        anchors.centerIn: parent
        icon.source: Qt.resolvedUrl("qrc:/icons/cart.svg")
        text: qsTr("No transactions took place on this day.")
    }

    QQC2.BusyIndicator {
        anchors.centerIn: parent
        visible: purchaseTransactionListView.model.busy
    }

    header: FluidControls.ListItem {
        width: ListView.view.width
        height: 40
        visible: ListView.view.count > 0
        showDivider: true

        FluidControls.ThinDivider {
            anchors {
                left: parent.left
                right: parent.right
                top: parent.top
            }
        }

        Row {
            spacing: 0
            anchors.verticalCenter: parent.verticalCenter

            Item { width: 24; height: 1 }

            FluidControls.SubheadingLabel {
                text: qsTr("ID")
                font.italic: true
            }

            Item { width: 64; height: 1 }

            FluidControls.SubheadingLabel {
                text: qsTr("Customer name")
            }

            Item { width: 400; height: 1 }

            FluidControls.SubheadingLabel {
                text: qsTr("Total cost")
            }
        }
    }

    model: RRModels.PurchaseTransactionModel {
        filterText: purchaseTransactionListView.filterText
        filterColumn: purchaseTransactionListView.filterColumn
        keys: purchaseTransactionListView.keys
        from: purchaseTransactionListView.from
        to: purchaseTransactionListView.to
        onSuccess: purchaseTransactionListView.success(successCode);
        onError: purchaseTransactionListView.error(errorCode);
    }

    QQC2.ScrollBar.vertical: QQC2.ScrollBar {
        policy: QQC2.ScrollBar.AlwaysOn
        visible: purchaseTransactionListView.contentHeight > purchaseTransactionListView.height
        size: .3
        width: 5
        contentItem: Rectangle {
            color: Material.color(Material.Grey)
            radius: width / 2
        }
    }

    delegate: FluidControls.ListItem {
        width: ListView.view.width
        height: 40
        showDivider: true

        Row {
            spacing: 0
            anchors.verticalCenter: parent.verticalCenter

            Item { width: 24; height: 1 }

            FluidControls.SubheadingLabel {
                text: ('0000000' + transaction_id).slice(-6)
                font.italic: true
            }

            Item { width: 32; height: 1 }

            FluidControls.SubheadingLabel {
                text: customer_name
            }
        }

        Row {
            spacing: 8
            anchors {
                right: parent.right
                verticalCenter: parent.verticalCenter
            }

            FluidControls.SubheadingLabel {
                text: Number(model.total_cost).toLocaleCurrencyString(Qt.locale(GlobalSettings.currencyLocaleName))
                verticalAlignment: Qt.AlignVCenter
                anchors.verticalCenter: parent.verticalCenter
            }

            Loader {
                id: rightButtonLoader

                readonly property var modelData: {
                    "client_id": model.client_id,
                            "transaction_id": model.transaction_id,
                            "customer_name": model.customer_name,
                            "row": index
                }

                anchors.verticalCenter: parent.verticalCenter
                sourceComponent: purchaseTransactionListView.buttonRow
            }
        }
    }

    add: Transition {
        NumberAnimation { property: "y"; from: 100; duration: 300; easing.type: Easing.OutCubic }
        NumberAnimation { property: "opacity"; to: 1; duration: 300; easing.type: Easing.OutCubic }
    }

    remove: Transition {
        NumberAnimation { property: "opacity"; to: 0; duration: 300; easing.type: Easing.OutCubic }
    }

    removeDisplaced: Transition {
        NumberAnimation { properties: "x,y"; duration: 300 }
    }
}