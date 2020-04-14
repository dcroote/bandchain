module RawDataReport = {
  type t = {
    externalDataID: int,
    data: JsBuffer.t,
  };

  let decode = json =>
    JsonUtils.Decode.{
      externalDataID: json |> field("externalDataID", int),
      data: json |> field("data", string) |> JsBuffer.fromBase64,
    };
};

module Msg = {
  module Send = {
    type t = {
      fromAddress: Address.t,
      toAddress: Address.t,
      amount: list(Coin.t),
    };

    let decode = json =>
      JsonUtils.Decode.{
        fromAddress: json |> field("from_address", string) |> Address.fromBech32,
        toAddress: json |> field("to_address", string) |> Address.fromBech32,
        amount: json |> field("amount", list(Coin.decodeCoin)),
      };
  };

  module CreateDataSource = {
    type t = {
      id: ID.DataSource.t,
      owner: Address.t,
      name: string,
      fee: list(Coin.t),
      executable: JsBuffer.t,
      sender: Address.t,
    };

    let decode = json =>
      JsonUtils.Decode.{
        id: json |> field("data_source_id", ID.DataSource.fromJson),
        owner: json |> field("owner", string) |> Address.fromBech32,
        name: json |> field("name", string),
        fee: json |> field("fee", list(Coin.decodeCoin)),
        executable: json |> field("executable", string) |> JsBuffer.fromBase64,
        sender: json |> field("sender", string) |> Address.fromBech32,
      };
  };

  module EditDataSource = {
    type t = {
      id: ID.DataSource.t,
      owner: Address.t,
      name: string,
      fee: list(Coin.t),
      executable: JsBuffer.t,
      sender: Address.t,
    };

    let decode = json =>
      JsonUtils.Decode.{
        id: json |> field("data_source_id", ID.DataSource.fromJson),
        owner: json |> field("owner", string) |> Address.fromBech32,
        name: json |> field("name", string),
        fee: json |> field("fee", list(Coin.decodeCoin)),
        executable: json |> field("executable", string) |> JsBuffer.fromBase64,
        sender: json |> field("sender", string) |> Address.fromBech32,
      };
  };

  module CreateOracleScript = {
    type t = {
      id: ID.OracleScript.t,
      owner: Address.t,
      name: string,
      code: JsBuffer.t,
      sender: Address.t,
    };

    let decode = json =>
      JsonUtils.Decode.{
        id: json |> field("oracle_script_id", ID.OracleScript.fromJson),
        owner: json |> field("owner", string) |> Address.fromBech32,
        name: json |> field("name", string),
        code: json |> field("code", string) |> JsBuffer.fromBase64,
        sender: json |> field("sender", string) |> Address.fromBech32,
      };
  };

  module EditOracleScript = {
    type t = {
      id: ID.OracleScript.t,
      owner: Address.t,
      name: string,
      code: JsBuffer.t,
      sender: Address.t,
    };

    let decode = json =>
      JsonUtils.Decode.{
        id: json |> field("oracle_script_id", ID.OracleScript.fromJson),
        owner: json |> field("owner", string) |> Address.fromBech32,
        name: json |> field("name", string),
        code: json |> field("code", string) |> JsBuffer.fromBase64,
        sender: json |> field("sender", string) |> Address.fromBech32,
      };
  };

  module Request = {
    type t = {
      id: ID.Request.t,
      oracleScriptID: ID.OracleScript.t,
      oracleScriptName: string,
      calldata: JsBuffer.t,
      requestedValidatorCount: int,
      sufficientValidatorCount: int,
      sender: Address.t,
    };

    let decode = json => {
      JsonUtils.Decode.{
        id: json |> field("request_id", ID.Request.fromJson),
        oracleScriptID: json |> field("oracleScriptID", ID.OracleScript.fromJson),
        oracleScriptName: json |> field("oracle_script_name", string),
        calldata: json |> field("calldata", string) |> JsBuffer.fromBase64,
        requestedValidatorCount: json |> field("requestedValidatorCount", int),
        sufficientValidatorCount: json |> field("sufficientValidatorCount", int),
        sender: json |> field("sender", string) |> Address.fromBech32,
      };
    };
  };

  module Report = {
    type t = {
      requestID: ID.Request.t,
      dataSet: list(RawDataReport.t),
      validator: Address.t,
      reporter: Address.t,
    };

    let decode = json =>
      JsonUtils.Decode.{
        requestID: json |> field("requestID", ID.Request.fromJson),
        dataSet: json |> field("dataSet", list(RawDataReport.decode)),
        validator: json |> field("validator", string) |> Address.fromBech32,
        reporter: json |> field("reporter", string) |> Address.fromBech32,
      };
  };
  module AddOracleAddress = {
    type t = {
      validator: Address.t,
      reporter: Address.t,
      validatorMoniker: string,
    };
    let decode = json =>
      JsonUtils.Decode.{
        validator: json |> field("validator", string) |> Address.fromBech32,
        reporter: json |> field("reporter", string) |> Address.fromBech32,
        validatorMoniker: json |> field("validator_moniker", string),
      };
  };

  module RemoveOracleAddress = {
    type t = {
      validator: Address.t,
      reporter: Address.t,
      validatorMoniker: string,
    };
    let decode = json =>
      JsonUtils.Decode.{
        validator: json |> field("validator", string) |> Address.fromBech32,
        reporter: json |> field("reporter", string) |> Address.fromBech32,
        validatorMoniker: json |> field("validator_moniker", string),
      };
  };

  module CreateValidator = {
    type t = {
      moniker: string,
      identity: string,
      website: string,
      details: string,
      commissionRate: float,
      commissionMaxRate: float,
      commissionMaxChange: float,
      delegatorAddress: Address.t,
      validatorAddress: Address.t,
      publicKey: PubKey.t,
      minSelfDelegation: float,
    };
    let decode = json =>
      JsonUtils.Decode.{
        moniker: json |> at(["description", "moniker"], string),
        identity: json |> at(["description", "identity"], string),
        website: json |> at(["description", "website"], string),
        details: json |> at(["description", "details"], string),
        commissionRate: json |> at(["commission", "rate"], floatstr),
        commissionMaxRate: json |> at(["commission", "max_rate"], floatstr),
        commissionMaxChange: json |> at(["commission", "max_change_rate"], floatstr),
        delegatorAddress: json |> field("delegator_address", string) |> Address.fromBech32,
        validatorAddress: json |> field("validator_address", string) |> Address.fromBech32,
        publicKey: json |> field("pubkey", string) |> PubKey.fromBech32,
        minSelfDelegation: json |> field("min_self_delegation", floatstr),
      };
  };

  module EditValidator = {
    type t = {
      moniker: string,
      identity: string,
      website: string,
      details: string,
      commissionRate: float,
      sender: Address.t,
      minSelfDelegation: float,
    };
    let decode = json =>
      JsonUtils.Decode.{
        moniker: json |> field("moniker", string),
        identity: json |> field("identity", string),
        website: json |> field("website", string),
        details: json |> field("details", string),
        commissionRate: json |> field("commission_rate", floatstr),
        sender: json |> field("address", string) |> Address.fromBech32,
        minSelfDelegation: json |> field("min_self_delegation", floatstr),
      };
  };

  module FailMessage = {
    type t = {
      sender: Address.t,
      message: string,
    };
    let decode = json =>
      JsonUtils.Decode.{
        sender: json |> field("sender", string) |> Address.fromBech32,
        message: json |> field("type", string),
      };
  };

  type t =
    | Unknown
    | Send(Send.t)
    | CreateDataSource(CreateDataSource.t)
    | EditDataSource(EditDataSource.t)
    | CreateOracleScript(CreateOracleScript.t)
    | EditOracleScript(EditOracleScript.t)
    | Request(Request.t)
    | Report(Report.t)
    | AddOracleAddress(AddOracleAddress.t)
    | RemoveOracleAddress(RemoveOracleAddress.t)
    | CreateValidator(CreateValidator.t)
    | EditValidator(EditValidator.t)
    | FailMessage(FailMessage.t);

  let getCreator = msg => {
    switch (msg) {
    | Send(send) => send.fromAddress
    | CreateDataSource(dataSource) => dataSource.sender
    | EditDataSource(dataSource) => dataSource.sender
    | CreateOracleScript(oracleScript) => oracleScript.sender
    | EditOracleScript(oracleScript) => oracleScript.sender
    | Request(request) => request.sender
    | Report(report) => report.reporter
    | AddOracleAddress(address) => address.validator
    | RemoveOracleAddress(address) => address.validator
    | CreateValidator(validator) => validator.delegatorAddress
    | EditValidator(validator) => validator.sender
    | FailMessage(fail) => fail.sender
    | Unknown => "" |> Address.fromHex
    };
  };

  let decodeAction = json => {
    JsonUtils.Decode.(
      switch (json |> field("type", string)) {
      | "send" => Send(json |> Send.decode)
      | "create_data_source" => CreateDataSource(json |> CreateDataSource.decode)
      | "edit_data_source" => EditDataSource(json |> EditDataSource.decode)
      | "create_oracle_script" => CreateOracleScript(json |> CreateOracleScript.decode)
      | "edit_oracle_script" => EditOracleScript(json |> EditOracleScript.decode)
      | "request" => Request(json |> Request.decode)
      | "report" => Report(json |> Report.decode)
      | "add_oracle_address" => AddOracleAddress(json |> AddOracleAddress.decode)
      | "remove_oracle_address" => RemoveOracleAddress(json |> RemoveOracleAddress.decode)
      | "create_validator" => CreateValidator(json |> CreateValidator.decode)
      | "edit_validator" => EditValidator(json |> EditValidator.decode)
      | _ => Unknown
      }
    );
  };

  let decodeFailAction = json => FailMessage(json |> FailMessage.decode);

  let decodeUnknowStatus = _ => {
    Js.Console.log("Error status messages field");
    [];
  };

  let decodeActions = json =>
    JsonUtils.Decode.(
      switch (json |> field("status", string)) {
      | "success" => json |> field("messages", list(decodeAction))
      | "failure" => json |> field("messages", list(decodeFailAction))
      | _ => json |> field("messages", decodeUnknowStatus)
      }
    );

  let getRoute = msg =>
    switch (msg) {
    | Send(account) =>
      Some(Route.AccountIndexPage(account.fromAddress, Route.AccountTransactions))
    | CreateDataSource(dataSource) => Some(dataSource.id |> ID.DataSource.getRoute)
    | EditDataSource(dataSource) => Some(dataSource.id |> ID.DataSource.getRoute)
    | CreateOracleScript(oracleScript) => Some(oracleScript.id |> ID.OracleScript.getRoute)
    | EditOracleScript(oracleScript) => Some(oracleScript.id |> ID.OracleScript.getRoute)
    | Request(request) => Some(request.id |> ID.Request.getRoute)
    | Report(report) => Some(report.requestID |> ID.Request.getRoute)
    | AddOracleAddress(account) =>
      Some(Route.AccountIndexPage(account.validator, Route.AccountTransactions))
    | RemoveOracleAddress(account) =>
      Some(Route.AccountIndexPage(account.validator, Route.AccountTransactions))
    | CreateValidator(validator) =>
      Some(Route.ValidatorIndexPage(validator.validatorAddress, Route.Delegators))
    | EditValidator(validator) =>
      Some(Route.ValidatorIndexPage(validator.sender, Route.Delegators))
    | FailMessage(_) => None
    | Unknown => None
    };
};

type t = {
  txHash: Hash.t,
  blockHeight: ID.Block.t,
  success: bool,
  gasFee: list(Coin.t),
  gasLimit: int,
  gasUsed: int,
  sender: Address.t,
  timestamp: MomentRe.Moment.t,
  messages: list(Msg.t),
};

module Mini = {
  type t = {
    txHash: Hash.t,
    blockHeight: ID.Block.t,
    timestamp: MomentRe.Moment.t,
  };
};

module SingleConfig = [%graphql
  {|
  subscription Transaction($tx_hash:bytea!) {
    transactions_by_pk(tx_hash: $tx_hash) @bsRecord {
      txHash : tx_hash @bsDecoder(fn: "GraphQLParser.hash")
      blockHeight: block_height @bsDecoder(fn: "ID.Block.fromJson")
      success
      gasFee: gas_fee @bsDecoder(fn: "GraphQLParser.coins")
      gasLimit: gas_limit @bsDecoder(fn: "GraphQLParser.int64")
      gasUsed : gas_used @bsDecoder(fn: "GraphQLParser.int64")
      sender  @bsDecoder(fn: "Address.fromBech32")
      timestamp  @bsDecoder(fn: "GraphQLParser.time")
      messages @bsDecoder(fn: "Msg.decodeActions")
    }
  },
|}
];

module MultiConfig = [%graphql
  {|
  subscription Transactions($limit: Int!, $offset: Int!) {
    transactions(offset: $offset, limit: $limit, order_by: {block_height: desc, index: desc}) @bsRecord {
      txHash : tx_hash @bsDecoder(fn: "GraphQLParser.hash")
      blockHeight: block_height @bsDecoder(fn: "ID.Block.fromJson")
      success
      gasFee: gas_fee @bsDecoder(fn: "GraphQLParser.coins")
      gasLimit: gas_limit @bsDecoder(fn: "GraphQLParser.int64")
      gasUsed : gas_used @bsDecoder(fn: "GraphQLParser.int64")
      sender  @bsDecoder(fn: "Address.fromBech32")
      timestamp  @bsDecoder(fn: "GraphQLParser.time")
      messages @bsDecoder(fn: "Msg.decodeActions")
    }
  }
|}
];

module MultiByHeightConfig = [%graphql
  {|
  subscription TransactionsByHeight($height: bigint!, $limit: Int!, $offset: Int!) {
    transactions(where: {block_height: {_eq: $height}}, offset: $offset, limit: $limit, order_by: {index: desc}) @bsRecord {
      txHash : tx_hash @bsDecoder(fn: "GraphQLParser.hash")
      blockHeight: block_height @bsDecoder(fn: "ID.Block.fromJson")
      success
      gasFee: gas_fee @bsDecoder(fn: "GraphQLParser.coins")
      gasLimit: gas_limit @bsDecoder(fn: "GraphQLParser.int64")
      gasUsed : gas_used @bsDecoder(fn: "GraphQLParser.int64")
      sender  @bsDecoder(fn: "Address.fromBech32")
      timestamp  @bsDecoder(fn: "GraphQLParser.time")
      messages @bsDecoder(fn: "Msg.decodeActions")
    }
  }
|}
];

module MultiBySenderConfig = [%graphql
  {|
  subscription TransactionsBySender($sender: String!, $limit: Int!, $offset: Int!) {
    transactions(
      where: {sender: {_eq: $sender}},
      offset: $offset,
      limit: $limit,
      order_by: {block_height: desc,index: desc},
    ) @bsRecord {
      txHash : tx_hash @bsDecoder(fn: "GraphQLParser.hash")
      blockHeight: block_height @bsDecoder(fn: "ID.Block.fromJson")
      success
      gasFee: gas_fee @bsDecoder(fn: "GraphQLParser.coins")
      gasLimit: gas_limit @bsDecoder(fn: "GraphQLParser.int64")
      gasUsed : gas_used @bsDecoder(fn: "GraphQLParser.int64")
      sender  @bsDecoder(fn: "Address.fromBech32")
      timestamp  @bsDecoder(fn: "GraphQLParser.time")
      messages @bsDecoder(fn: "Msg.decodeActions")
    }
  }
|}
];

module TxCountConfig = [%graphql
  {|
  subscription TransactionsCount {
    transactions_aggregate {
      aggregate {
        count @bsDecoder(fn: "Belt_Option.getExn")
      }
    }
  }
|}
];

module TxCountBySenderConfig = [%graphql
  {|
  subscription TransactionsCountBySender($sender: String!) {
    transactions_aggregate(where: {sender: {_eq: $sender}}) {
      aggregate {
        count @bsDecoder(fn: "Belt_Option.getExn")
      }
    }
  }
|}
];

let get = txHash => {
  let (result, _) =
    ApolloHooks.useSubscription(
      SingleConfig.definition,
      ~variables=
        SingleConfig.makeVariables(
          ~tx_hash=txHash |> Hash.toHex |> (x => "\\x" ++ x) |> Js.Json.string,
          (),
        ),
    );
  let%Sub x = result;
  switch (x##transactions_by_pk) {
  | Some(data) => Sub.resolve(data)
  | None => NoData
  };
};

let getList = (~page, ~pageSize, ()) => {
  let offset = (page - 1) * pageSize;
  let (result, _) =
    ApolloHooks.useSubscription(
      MultiConfig.definition,
      ~variables=MultiConfig.makeVariables(~limit=pageSize, ~offset, ()),
    );
  result |> Sub.map(_, x => x##transactions);
};

let getListBySender = (sender, ~page, ~pageSize, ()) => {
  let offset = (page - 1) * pageSize;
  let (result, _) =
    ApolloHooks.useSubscription(
      MultiBySenderConfig.definition,
      ~variables=
        MultiBySenderConfig.makeVariables(
          ~sender=sender |> Address.toBech32,
          ~limit=pageSize,
          ~offset,
          (),
        ),
    );
  result |> Sub.map(_, x => x##transactions);
};

let getListByBlockHeight = (height, ~page, ~pageSize, ()) => {
  let offset = (page - 1) * pageSize;
  let (result, _) =
    ApolloHooks.useSubscription(
      MultiByHeightConfig.definition,
      ~variables=
        MultiByHeightConfig.makeVariables(
          ~height=height |> ID.Block.toJson,
          ~limit=pageSize,
          ~offset,
          (),
        ),
    );
  result |> Sub.map(_, x => x##transactions);
};

let count = () => {
  let (result, _) = ApolloHooks.useSubscription(TxCountConfig.definition);
  result
  |> Sub.map(_, x => x##transactions_aggregate##aggregate |> Belt_Option.getExn |> (y => y##count));
};

let countBySender = sender => {
  let (result, _) =
    ApolloHooks.useSubscription(
      TxCountBySenderConfig.definition,
      ~variables=TxCountBySenderConfig.makeVariables(~sender=sender |> Address.toBech32, ()),
    );
  result
  |> Sub.map(_, x => x##transactions_aggregate##aggregate |> Belt_Option.getExn |> (y => y##count));
};
